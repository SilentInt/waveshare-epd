#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <SdFat.h>
#include <WebServer.h>

using namespace std;

extern SdFat sd;
WebServer server(80);

// 扫描wifi
void scanwifi() {
  int n = WiFi.scanComplete();
  if (n == -2) {
    WiFi.scanNetworks(true);
  } else if (n) {
    Serial.println("scan done");
    // 创建json
    JsonDocument doc;
    JsonArray array = doc.to<JsonArray>();
    for (int i = 0; i < n; ++i) {
      JsonDocument obj;
      obj["ssid"] = WiFi.SSID(i);
      obj["rssi"] = WiFi.RSSI(i);
      obj["encryption"] = WiFi.encryptionType(i);
      doc.add(obj);
    }
    WiFi.scanDelete();
    if (WiFi.scanComplete() == -2) {
      WiFi.scanNetworks(true);
    }
    String json_str;
    serializeJson(doc, json_str);
    server.send(200, "application/json", json_str);
  } else {
    server.send(200, "text/plain", "scan failed");
  }
}

// 保存wifi配置
void wifi_commit() {
  // 获取请求体的内容
  String body = server.arg("plain");
  Serial.println(body);
  // 解析json
  JsonDocument reqjson;
  deserializeJson(reqjson, body);
  String ssid = reqjson["ssid"].as<String>();
  String passwd = reqjson["passwd"].as<String>();
  // 将ssid和passwd写入SPIFFS
  File file = SPIFFS.open("/wifi.conf", FILE_WRITE);
  if (!file) {
    Serial.println("open file failed");
  }
  file.println(ssid);
  file.println(passwd);
  file.close();
  server.send(200, "text/plain", "ok");
  // 重启
  ESP.restart();
}

// wifi配置页面
void wifi_list() {
  Serial.println("wifi_list");
  // 返回SPIFFS下的wifi.html
  File file = SPIFFS.open("/wifi.html");
  if (!file) {
    Serial.println("file open failed");
    return;
  }
  String html = file.readString();
  file.close();
  server.send(200, "text/html", html);
}

// 接收前端上传的文件
void handle_upload() {
  HTTPUpload &upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    Serial.println("upload file name: " + filename);
    // 检查文件是否存在
    if (sd.exists(filename)) {
      Serial.println("file exists. Overwrite it.");
      sd.remove(filename);
    }
    // 将文件写入SD卡
    FsFile file = sd.open(filename, O_WRITE | O_CREAT | O_TRUNC);
    if (!file) {
      Serial.println("open file failed");
    }
    file.close();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    Serial.println("upload file data");
    // 将文件写入SD卡
    FsFile file = sd.open(upload.filename, O_APPEND);
    if (!file) {
      Serial.println("open file failed");
    }
    file.write(upload.buf, upload.currentSize);
    file.close();
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.println("upload file end");
    server.send(200, "text/plain", "ok");
  }
}

JsonDocument get_file_ls(String path) {
  // 打开根目录
  FsFile root;
  FsFile file;
  root.open(path.c_str(), O_RDONLY);
  if (!root) {
    Serial.println("open root failed");
  }
  // root.ls(LS_R | LS_DATE | LS_SIZE);
  // 创建json
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();
  root.rewind();
  while (file.openNext(&root, O_RDONLY)) {
    if (file.isHidden()) {
      continue;
    }
    JsonDocument obj;
    char name[256];
    file.getName(name, sizeof(name));
    obj["name"] = String(name);
    obj["size"] = file.size();
    obj["isDir"] = file.isDir();
    doc.add(obj);
  }
  return doc;
}

void file_page() {
  Serial.println("file_page");
  // 返回SPIFFS下的file.html
  File file = SPIFFS.open("/file.html");
  if (!file) {
    Serial.println("file open failed");
    return;
  }
  String html = file.readString();
  file.close();
  server.send(200, "text/html", html);
}

void file_ls() {
  Serial.println("file_ls");
  // 获取请求体的内容
  String body = server.arg("plain");
  Serial.println(body);
  Serial.println("file_ls_json");
  // 打印选中的文件
  JsonDocument reqjson;
  deserializeJson(reqjson, body);
  String name = reqjson["filename"].as<String>();
  Serial.println("select file: " + name);
  FsFile file;
  file.open(name.c_str(), O_RDONLY);
  if (!file) {
    Serial.println("open file failed");
  }
  // 组装返回的json
  JsonDocument resbody;
  bool is_dir = file.isDir();
  resbody["isDir"] = is_dir;
  // 如果是文件夹则返回文件夹下的文件列表
  if (is_dir) {
    JsonDocument data = get_file_ls(name);
    resbody["data"] = data;
  } else {
    // 如果是文件则 返回文件内容
    Serial.println("open file: " + name);
    // 读取文件内容
    String content = "";
    while (file.available()) {
      content += (char)file.read();
    }
    Serial.println(content);
    // 序列化json
    JsonDocument json;
    json["name"] = name;
    json["content"] = content;
    resbody["data"] = json;
  }
  String json_str;
  serializeJson(resbody, json_str);
  // 返回文件内容
  server.send(200, "application/json", json_str);
}

// 使用Webserver重写createServer
void createServer() {
  server.on("/wifi/scan", HTTP_GET, scanwifi);
  server.on("/wifi", HTTP_GET, wifi_list);
  server.on("/wifi", HTTP_POST, wifi_commit);
  server.on("/file/upload", HTTP_POST, handle_upload);
  server.on("/file", HTTP_GET, file_page);
  server.on("/file", HTTP_POST, file_ls);
  server.begin();
}