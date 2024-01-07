#include "hal.h"

void spiffs_init() {
  if (!SPIFFS.begin(true)) {
    Serial.println("opening SPIFFS");
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  Serial.println("SPIFFS OK!");
}