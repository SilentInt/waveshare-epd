#ifndef __HAL_H__
#define __HAL_H__

// #include "epd_driver/DEV_Config.h"

#define WIFI 1
#define WEB 1
#define SD_USE 1
#define BUTTON_USE 1

#if WIFI
// #define FS_NO_GLOBALS
void spiffs_init();  // 初始化SPIFFS
void connectWifi();  // 从SPIFFS中读取wifi配置连接wifi，若失败则进入配网模式
#endif

#if WEB
void createServer();  // 创建WebServer
#endif

#if SD_USE
// SD卡IO定义
#define SD_CS_PIN 21
#define SD_MISO_PIN 2
#define SD_MOSI_PIN 20
#define SD_SCK_PIN 42
// SD卡类型
#define SD_FAT_TYPE 3
void sd_init();  // 初始化SD卡
#endif

#if BUTTON_USE
// 按钮IO定义
#define BUTTON_SUP_PIN 41
#define BUTTON_SDOWN_PIN 40
#define BUTTON_SCUR_PIN 39
void button_init();  // 初始化按钮
void btn_ticks();    // 按钮轮询

#endif

// 初始化HAL
void hal_init();
#endif