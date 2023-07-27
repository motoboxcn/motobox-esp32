#include <gy91.ino>
#include <lvgl.h>
#include <dashboard.ino>
#include <L76X.ino>

void setup()
{
  Serial.begin(115200);
  dashboardInit();
  // apps
  setupGy91();
  setupL76X();
  Serial.println("Setup done");
}

void loop()
{
  LoopL76X();
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}