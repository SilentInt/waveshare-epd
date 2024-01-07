#include "hal.h"

void hal_init() {
  Serial.begin(115200);
  // spiffs_init();
  // 从SPIFFS中读取wifi配置连接wifi，若失败则进入配网模式
  // connectWifi();
  // 创建WebServer
  // createServer();
  // 初始化EPD_GPIO
  DEV_Module_Init();
}