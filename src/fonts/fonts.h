/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONTS_H
#define __FONTS_H

/* Max size of bitmap will based on a font24 (17x24) */
#define MAX_HEIGHT_FONT 41
#define MAX_WIDTH_FONT 32
#define OFFSET_BITMAP 54

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
// #include <avr/pgmspace.h>
// ASCII
typedef struct _tFont {
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;

} sFONT;

// GB2312
typedef struct  // 汉字字模数据结构
{
  const char index[4];  // 汉字内码索引
  const uint8_t matrix[MAX_HEIGHT_FONT * MAX_WIDTH_FONT / 8];  // 点阵码数据
} CH_CN;

typedef struct {
  const CH_CN *table;
  uint16_t size;
  uint16_t ASCII_Width;
  uint16_t Width;
  uint16_t Height;

} cFONT;

// extern sFONT Font24;
// extern sFONT Font20;
// extern sFONT Font16;
// extern sFONT Font12;
// extern sFONT Font8;
//
// extern cFONT Font12CN;
// extern cFONT Font24CN;
extern cFONT Font14CN;
extern cFONT Font16CN;

// extern const unsigned char Font16_Table[];

#ifdef __cplusplus
}
#endif

#endif /* __FONTS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
