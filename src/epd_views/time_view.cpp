#include "views.h"

void draw_time(int x, int y, int hour, int minute, int second) {
  int gap = 2;
  Paint_DrawIcon(lcd_numbers[hour / 10].data, x, y, 32, 64, BLACK, 1);
  Paint_DrawIcon(lcd_numbers[hour % 10].data, x + 32 + gap, y, 32, 64, BLACK,
                 1);
  Paint_DrawIcon(lcd_numbers[10].data, x + 64 + gap * 2, y, 32, 64, BLACK, 1);
  Paint_DrawIcon(lcd_numbers[minute / 10].data, x + 96 + gap * 3, y, 32, 64,
                 BLACK, 1);
  Paint_DrawIcon(lcd_numbers[minute % 10].data, x + 128 + gap * 4, y, 32, 64,
                 BLACK, 1);
}

/*
 * 展示时间页面
 * -------------------------------------------------------------
 * param: BlackImage 黑色图像缓存
 * param: RedImage 红色图像缓存(暂时不用)
 */
void time_view_bwr(UBYTE *BlackImage, UBYTE *RedImage) {
  Serial.println("time_view_bwr");
  Paint_SelectImage(BlackImage);
  Paint_DrawRectangle(0, 0, Paint.Width * 0.4, Paint.Height, BLACK,
                      DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_Draw_String(Paint.Width * 0.4 + 2, 2, "2024年1月2日 星期二", &Font14CN,
                    BLACK, WHITE, 1);
  Paint_Draw_String(Paint.Width * 0.4 + 2, 2 + Font14CN.Height,
                    "这里来点农历日期", &Font14CN, BLACK, WHITE, 1);
  int y_b = 5 + Font14CN.Height * 2;
  int offset = Paint.Width * 0.4 + 4;
  draw_time(offset, y_b, 23, 59, 59);

  y_b = 5 + Font14CN.Height * 2 + 64;
  Paint_Draw_String(Paint.Width * 0.4 + 2, y_b, "每天一只猫猫，医生远离我!",
                    &Font16CN, BLACK, WHITE, 1);
  // Paint_DrawImage(sunny.data, 0, 0, sunny.width, sunny.height);
  Paint_DrawIcon(sunny.data, Paint.Width * 0.2 - sunny.width * 0.5,
                 Paint.Height * 0.25 - sunny.height * 0.5, sunny.width,
                 sunny.height, WHITE, 1);
  Paint_DrawLine(0, Paint.Height / 2, Paint.Width * 0.4, Paint.Height / 2,
                 WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}

/*
 * 展示时间页面
 * -------------------------------------------------------------
 * param: BlackImage 黑色图像缓存
 */
void time_view_bw(UBYTE *Image) { time_view_bwr(Image, NULL); }