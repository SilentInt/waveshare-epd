#include "views.h"

// 黑白屏
#ifdef EPD_BW
void create_view_bw(view_func_bw func) {
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
  Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);

  // 清空图片
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 调用视图渲染函数
  func(BlackImage);
#ifndef ESP32
  renderScreen(BlackImage, RedImage);
#else
  // 初始化
  EPD_Init();
  // EPD_Clear();
  // 展示后休眠
  EPD_Display(BlackImage);
  EPD_Sleep();
#endif
  free(BlackImage);
}
#endif
