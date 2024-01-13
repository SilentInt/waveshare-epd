#include "HAL/hal.h"
#include "epd_views/views.h"
// TXT阅读器
typedef struct {
  uint64_t page;
  String filename;
} TXT_Info;

// 阅读器渲染刷新视图函数, 用于创建视图
void txt_reader(UBYTE *image);
// 向下翻页
void txt_reader_down();
// 向上翻页
void txt_reader_up();
// 全局刷新去除残影
void txt_reader_refresh();
