#include "hal.h"

#include "epd_driver/DEV_Config.h"

void hal_init() {
  Serial.begin(115200);
#if WIFI
  spiffs_init();
  // 从SPIFFS中读取wifi配置连接wifi，若失败则进入配网模式
  connectWifi();
#endif
#if WEB
  // 创建WebServer
  createServer();
#endif
#if SD_USE
  sd_init();
#endif
  // 初始化EPD_GPIO
  DEV_Module_Init();
}