#ifndef __HAL_H__
#define __HAL_H__

// #include "epd_driver/DEV_Config.h"

#define WIFI 1
#define WEB 1
#define SD_USE 1

#if WIFI
// #define FS_NO_GLOBALS
void spiffs_init();
// 从SPIFFS中读取wifi配置连接wifi，若失败则进入配网模式
void connectWifi();
#endif

#if WEB
// 创建WebServer
void createServer();
#endif

#if SD_USE
#define SD_CS_PIN 21
#define SD_MISO_PIN 2
#define SD_MOSI_PIN 20
#define SD_SCK_PIN 42
#define SD_FAT_TYPE 3
// 初始化SD卡
// extern SdFat sd;
void sd_init();
#endif

// 初始化HAL
void hal_init();
#endif