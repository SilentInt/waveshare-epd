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
}

// 连接WIFI ssid passwd
void connectWifi() {
  // 从SPIFFS中读取ssid和passwd
  String ssid = "", passwd = "";
  if (SPIFFS.exists("/wifi.conf")) {
    File file = SPIFFS.open("/wifi.conf", FILE_READ);
    if (file) {
      ssid = file.readStringUntil('\n').substring(0, ssid.length() - 1);
      passwd = file.readStringUntil('\n').substring(0, passwd.length() - 1);
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
        APMode();
      }
    }
  } else {
    // 如果不存在wifi.conf文件，则开启AP模式
    Serial.println("wifi.conf not exists");
    APMode();
  }
}