#ifndef __HAL_H__
#define __HAL_H__

#include <SPIFFS.h>
#include <WiFi.h>

#include "epd_driver/DEV_Config.h"

void spiffs_init();
// 从SPIFFS中读取wifi配置连接wifi，若失败则进入配网模式
void connectWifi();
// 创建WebServer
void createServer();
// 初始化HAL
void hal_init();
#endif