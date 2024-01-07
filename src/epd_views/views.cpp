#include "views.h"

// 共用函数

// 屏幕休眠
void screenHibernate() {
  Serial.println("EPD_Sleep");
  // EPD_Init();
  EPD_Sleep();
}
// 清空屏幕
void screenClear() {
  Serial.println("EPD_Clear");
  EPD_Init();
  EPD_Clear();
  screenHibernate();
}