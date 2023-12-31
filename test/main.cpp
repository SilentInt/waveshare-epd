#include "epd_driver/EPD.h"
#include "ImageData.h"
#include <stdlib.h>

void setup() {
  printf("EPD_2IN66B_test Demo\r\n");
  DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_Init();
  EPD_Clear();
  DEV_Delay_ms(10);

  // Create a new image cache
  UBYTE* BlackImage, * RedImage;

  UWORD Imagesize = ((EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
  if ((BlackImage = (UBYTE*)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1)
      ;
  }
  if ((RedImage = (UBYTE*)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1)
      ;
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);
  Paint_NewImage(RedImage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);

#if 0 // show image for array
  printf("show image for array\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawBitMap(gImage_2in66bb);

  Paint_SelectImage(RedImage);
  Paint_Clear(WHITE);
  Paint_DrawBitMap(gImage_2in66br);

  EPD_2IN66B_Display(BlackImage, RedImage);
  DEV_Delay_ms(2000);
#endif

#if 0 // Drawing on the image
    // 1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 2.Drawing on the image
  printf("Drawing:BlackImage\r\n");
  Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

  Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

  Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  Paint_SelectImage(RedImage);
  Paint_Clear(WHITE);
  Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

  Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
  Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);

  Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
  Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

  Paint_DrawString_CN(130, 0, "你好abc", &Font12CN, BLACK, WHITE);
  Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, WHITE, BLACK);

  EPD_2IN66B_Display(BlackImage, RedImage);
  DEV_Delay_ms(4000);
#endif

  Serial.println("Show first words");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawString_Transparent(130, 20, "微雪电子", &Font24CN,
    WHITE, BLACK, 1);

  Paint_SelectImage(RedImage);
  Paint_Clear(WHITE);
  EPD_Display(BlackImage, RedImage);
  // delay(2000);

  Serial.println("sleep");
  EPD_Sleep();
  delay(2000);
  EPD_Init();

  Serial.println("Show second words");
  Paint_SelectImage(BlackImage);
  Paint_DrawString_Transparent(130, 20, "树莓派", &Font24CN,
    BLACK, WHITE, 0);
  EPD_Display(BlackImage, RedImage);
  delay(2000);


  printf("Clear...\r\n");
  EPD_Clear();

  printf("Goto Sleep...\r\n");
  EPD_Sleep();

  free(BlackImage);
  BlackImage = NULL;
  free(RedImage);
  RedImage = NULL;
  // close 5V
  printf("close 5V, Module enters 0 power consumption ...\r\n");
}

/* The main loop -------------------------------------------------------------*/
void loop() {
    //
}
