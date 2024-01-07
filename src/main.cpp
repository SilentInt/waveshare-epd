#include "HAL/hal.h"
#include "epd_views/views.h"

void setup() {
  hal_init();
  screenClear();
  create_view_bwr(time_view_bwr);
  delay(2000);
  screenClear();
}

/* The main loop
 * -------------------------------------------------------------*/
void loop() {}
