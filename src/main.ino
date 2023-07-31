#include <gy91.ino>
#include <lvgl.h>
#include <L76X.ino>
// #include <battery.ino>
#include <wifi.ino>


void setup()
{
  Serial.begin(115200);
  dashboardInit();
  // apps
  // setupGy91();
  setupL76X();
  setupWifi();
  // setup_adc();
  Serial.println("Setup done");
}

void loop()
{
  LoopL76X();
  loopWifi();
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}