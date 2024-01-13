#include <SPIFFS.h>
#include <WiFi.h>
// #include "hal.h"

// using namespace fs;
// AP并扫描附近的wifi
void APMode() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32-AP");
  Serial.println("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  WiFi.scanNetworks(true);
}

// 连接WIFI ssid passwd
void connectWifi() {
  // 从SPIFFS中读取ssid和passwd
  String ssid = "", passwd = "";
  if (SPIFFS.exists("/wifi.conf")) {
    File file = SPIFFS.open("/wifi.conf", FILE_READ);
    if (file) {
      ssid = file.readStringUntil('\n');
      passwd = file.readStringUntil('\n');
      // 去除末尾的换行符
      ssid.trim();
      passwd.trim();
      file.close();
      Serial.println("Connecting to [" + ssid + "]");
      Serial.println("passwd: [" + passwd + "]");
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, passwd);
      // 等待连接
      int timeout = 0;
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        // 等待20s
        if (timeout++ > 20) {
          Serial.println("Connect wifi timeout");
          break;
        }
        Serial.print(".");
      }
      // 判断是否连接成功
      if (WiFi.status() == WL_CONNECTED) {
        // 连接成功
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
      } else {
        // 连接失败，开启AP模式
        Serial.println("Connect wifi failed. Password error?");
        WiFi.disconnect();
        APMode();
      }
    }
  } else {
    // 如果不存在wifi.conf文件，则开启AP模式
    Serial.println("wifi.conf not exists");
    APMode();
  }
}