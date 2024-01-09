#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include "epd_views/views.h"
#include "hal.h"

using namespace std;
// 创建Server对象
AsyncWebServer server(80);

// 读取SPIFFS中index.html文件的内容，并使用网页展示
void handleRoot(AsyncWebServerRequest *request) {
  File file = SPIFFS.open("/index.html", FILE_READ);
  if (!file) {
    Serial.println("open file failed");
  }
  String content = file.readString();
  // server.send(200, "text/html", content);
  request->send(200, "text/html", content);
  file.close();
}

// 扫描wifi
void scanwifi(AsyncWebServerRequest *request) {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  vector<String> ssid_list;
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      ssid_list.push_back(WiFi.SSID(i));
    }
  }
  // 将ssid_list转换为,分割
  String ssids = "";
  for (int i = 0; i < ssid_list.size(); i += 2) {
    ssids += ssid_list[i];
    // 最后一个不含,
    if (i != ssid_list.size() - 2) {
      ssids += ",";
    }
  }
  Serial.println(ssids);
  // 返回结果
  request->send(200, "text/plain", ssids);
}

// 打印文件树
void print_tree(File root, int level) {
  while (true) {
    File file = root.openNextFile();
    if (!file) {
      break;
    }
    for (int i = 0; i < level; i++) {
      Serial.print("  ");
    }
    Serial.println(file.name());
    if (file.isDirectory()) {
      print_tree(file, level + 1);
    }
    file.close();
  }
}

// 保存wifi配置
void wifi_commit(AsyncWebServerRequest *request) {
  // String ssid = server.arg("ssid");
  // String passwd = server.arg("passwd");
  String ssid = request->arg("ssid");
  String passwd = request->arg("passwd");
  Serial.println("ssid: " + ssid);
  Serial.println("passwd: " + passwd);
  // 将ssid和passwd写入SPIFFS
  File file = SPIFFS.open("/wifi.conf", FILE_WRITE);
  if (!file) {
    Serial.println("open file failed");
  }
  file.println(ssid);
  file.println(passwd);
  file.close();
  request->send(200, "text/plain", "ok");
  // 重启
  ESP.restart();
}

// 接受前端的post请求体并保存
void text(AsyncWebServerRequest *request) {
  Serial.println("text");
  if (request->hasParam("data", true)) {
    String text = request->arg("data");
    // 保存到SPIFFS /text.txt
    File file = SPIFFS.open("/text.txt", FILE_WRITE);
    if (!file) {
      Serial.println("open file failed");
    }
    file.print(text);
    file.close();
    Serial.println(text);
  }
  request->send(200, "text/plain", "ok");
  delay(20);
  create_view_bw(txt_reader, 1);
}

// 接受前端发送的文件并保存
void file_upload(AsyncWebServerRequest *request, const String &filename,
                 size_t index, uint8_t *data, size_t len, bool final) {
  // 提交路径过滤
  // if (request->url() != "/file/upload") {
  //   request->send(404, "text/plain", "Not found");
  //   return;
  // }
  File file;
  // 创建/打开文件
  if (!index) {
    Serial.printf("UploadStart: %s\n", filename.c_str());
    // 保存到SPIFFS
    file = SPIFFS.open("/" + filename, FILE_WRITE);
  } else {
    file = SPIFFS.open("/" + filename, FILE_APPEND);
  }
  if (!file) {
    Serial.println("open file failed");
  }
  // 数据写入文件
  for (size_t i = 0; i < len; i++) {
    // 写入文件
    file.write(data[i]);
  }
  // 关闭文件
  if (final) {
    Serial.printf("UploadEnd: %s, %u B\n", filename.c_str(), index + len);
    file.close();
  }
}

void file_list(AsyncWebServerRequest *request) {
  // 读取SPIFFS中的文件列表
  File root = SPIFFS.open("/");
  String json = "[";
  while (true) {
    File file = root.openNextFile();
    if (!file) {
      break;
    }
    json += "\"" + String(file.name()) + "\",";
    file.close();
  }
  json = json.substring(0, json.length() - 1);
  json += "]";
  Serial.println(json);
  request->send(200, "application/json", json);
}

void file_select(AsyncWebServerRequest *request) {
  Serial.println("file_select");
  // 打印选中的文件
  if (request->hasParam("fileName", true)) {
    String fileName = request->arg("fileName");
    Serial.println("file: " + fileName);
    // 打印文件内容
    File file = SPIFFS.open("/" + fileName, FILE_READ);
    if (!file) {
      Serial.println("open file failed");
    }
    // 打印全部内容
    Serial.println(file.readString());
  }
  request->send(200, "text/plain", "ok");
}

void createServer() {
  // 主页
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  // wifi配置页面
  server.serveStatic("/wifi", SPIFFS, "/wifipage.html");
  server.on("/scanwifi", HTTP_GET, scanwifi);  // 扫描wifi
  server.on("/wifi_commit", wifi_commit);      // 保存wifi配置
  // 在线传输文本
  server.serveStatic("/text", SPIFFS, "/text.html");  // 文本传输页面
  server.on("/text_commit", HTTP_POST, text);  // 接受前端的post请求体并保存
  // 文件列表
  server.serveStatic("/file", SPIFFS, "/file.html");
  // 返回json格式的文件列表
  server.on("/file/list", HTTP_GET, file_list);       // 文件列表
  server.on("/file/select", HTTP_POST, file_select);  // 选中文件
  // 在线传书
  server.onFileUpload(file_upload);  // 接受前端的post请求体并保存

  // 404
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("HTTP server started");
}