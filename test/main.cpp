#include <Arduino.h>
#include <OneButton.h>
#include <SdFat.h>

OneButton btn_sup(41, true, true);
OneButton btn_sdown(40, true, true);
OneButton btn_scur(39, true, true);
void fbtn_sup() { Serial.println("波轮上"); }
void fbtn_sdown() { Serial.println("波轮下"); }
void fbtn_scur() { Serial.println("波轮按"); }

void ticks() {
  btn_sup.tick();    // 波轮上
  btn_sdown.tick();  // 波轮下
  btn_scur.tick();   // 波轮按
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  btn_sup.attachClick(fbtn_sup);
  btn_sdown.attachClick(fbtn_sdown);
  btn_scur.attachClick(fbtn_scur);
}

void loop() {
  // 监测按钮状态
  ticks();
}
