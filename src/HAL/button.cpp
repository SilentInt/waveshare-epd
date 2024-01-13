#include <OneButton.h>

#include "epd_views/txt_reader.h"
#include "hal.h"

OneButton btn_sup(BUTTON_SUP_PIN, true, true);
OneButton btn_sdown(BUTTON_SDOWN_PIN, true, true);
OneButton btn_scur(BUTTON_SCUR_PIN, true, true);

void fbtn_sup() {
  Serial.println("波轮上");
  txt_reader_up();
}
void fbtn_sdown() {
  Serial.println("波轮下");
  txt_reader_down();
}
void fbtn_scur() {
  Serial.println("波轮按");
  txt_reader_refresh();
}

void btn_ticks() {
  btn_sup.tick();    // 波轮上
  btn_sdown.tick();  // 波轮下
  btn_scur.tick();   // 波轮按
}

void button_init() {
  btn_sup.attachClick(fbtn_sup);
  btn_sdown.attachClick(fbtn_sdown);
  btn_scur.attachClick(fbtn_scur);
}