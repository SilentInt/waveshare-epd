#ifndef __EPDSSD1608_H_
#define __EPDSSD1608_H_

#include "../DEV_Config.h"

// 4.2inch e-Paper b
// #define EPD_WIDTH 400
// #define EPD_HEIGHT 300
// 2.66inch e-Paper b
#define EPD_WIDTH 152
#define EPD_HEIGHT 296

void EPD_SSD1680_Init(void);
void EPD_SSD1680_Display(UBYTE *ImageBlack, UBYTE *ImageRed);
void EPD_SSD1680_Clear(void);
void EPD_SSD1680_Sleep(void);
#endif
