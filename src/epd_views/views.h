#ifndef __VIEWS_H__
#define __VIEWS_H__
// #include <cstddef>

#include "epd_driver/GUI_Paint.h"
#include "fonts/fonts.h"
#include "icons/icons.h"
// GUI仿真器
#ifndef ESP32
#include "display.h"
#endif

// 定义芯片型号
// #define EPD_TYPE SSD1680
#define UC8151C

// 定义函数别名
// 当前芯片为SSD1680
#ifdef SSD1680

// 根据型号引入驱动
#include "epd_driver/chips/EPD_SSD1680.h"
#define EPD_Init EPD_SSD1680_Init
#define EPD_Clear EPD_SSD1680_Clear
#define EPD_Display EPD_SSD1680_Display
#define EPD_Sleep EPD_SSD1680_Sleep
#endif

#ifdef UC8151C
// 根据型号引入驱动
#include "epd_driver/chips/EPD_UC8151C.h"
#define EPD_Init EPD_2IN9D_Init
#define EPD_Clear EPD_2IN9D_Clear
#define EPD_Display EPD_2IN9D_Display
#define EPD_DisplayPart EPD_2IN9D_DisplayPart
#define EPD_Sleep EPD_2IN9D_Sleep
#endif

// 定义屏幕颜色(只留一个)
#define EPD_BW
// #define EPD_BWR

#ifdef EPD_BW
typedef void (*view_func_bw)(UBYTE *Image);  // 黑白屏的视图函数
void create_view_bw(view_func_bw func, UBYTE mode);  // 创建一个黑白的视图
void time_view_bw(UBYTE *Image);                     // 展示时间页面
#endif

#ifdef EPD_BWR

typedef void (*view_func_bwr)(UBYTE *BlackImage,
                              UBYTE *RedImage);  // 黑白红屏的视图函数
void create_view_bwr(view_func_bwr func);  // 创建一个黑白红的视图
void time_view_bwr(UBYTE *BlackImage, UBYTE *RedImage);  // 展示时间页面
#endif

// 共用函数
// 清空屏幕
void screenClear();
// 屏幕休眠
void screenHibernate();
#endif