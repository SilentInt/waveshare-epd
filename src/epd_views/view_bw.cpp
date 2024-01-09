#define FS_NO_GLOBALS
#include "views.h"

// 黑白屏
#ifdef EPD_BW
/*
 * @description: 创建一个黑白屏视图
 * @param {view_func_bw} func 视图渲染函数
 * @param {UBYTE} mode 渲染模式(全屏/局部)(0/1)
 * @return {*}
 */
void create_view_bw(view_func_bw func, UBYTE mode) {
  // 创建一个新的图片缓存
  UBYTE *BlackImage;
  UWORD Imagesize =
      ((EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1)) *
      EPD_HEIGHT;

  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1)
      ;
  }
  Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);

  // 清空图片
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 调用视图渲染函数
  func(BlackImage);
#ifndef ESP32
  renderScreen_bw(BlackImage);
#else
  // 初始化
  EPD_Init();
  // EPD_Clear();
  // 展示后休眠
  if (mode == 0)
    EPD_Display(BlackImage);
  else
    EPD_DisplayPart(BlackImage);
  screenHibernate();
#endif
  free(BlackImage);
}
#endif
