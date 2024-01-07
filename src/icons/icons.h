#ifndef __ICONS_H__
#define __ICONS_H__
#include <cstdint>
typedef struct {
  uint8_t width;
  uint8_t height;
  uint8_t *data;
} ICON;
extern ICON sunny;
extern ICON lcd_numbers[];

#endif
