#include "views.h"

// 共用函数

// 墨水屏是否休眠
bool is_sleep = true;
// 屏幕休眠
void screenHibernate() {
  Serial.println("EPD_Sleep");
  // EPD_Init();
  EPD_Sleep();
  is_sleep = true;
}
// 清空屏幕
void screenClear() {
  Serial.println("EPD_Clear");
  EPD_Init();
  EPD_Clear();
  screenHibernate();
}