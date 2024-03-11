# 1 "/var/folders/64/xyvthqtj4xqb6xp70kw9hgf80000gq/T/tmp35p_f23o"
#include <Arduino.h>
# 1 "/Users/mikas/Documents/github/motobox-esp32/src/main.ino"

#include <lvgl.h>
#include <TaskScheduler.h>
#include "core/dashboard.ino"
# 13 "/Users/mikas/Documents/github/motobox-esp32/src/main.ino"
void setup();
void loop();
#line 13 "/Users/mikas/Documents/github/motobox-esp32/src/main.ino"
void setup()
{
  Serial.begin(115200);

  LVSetup();


  ui_init();


  ShowSpeed();







}

void loop()
{

  Serial.println("Loop");
  delay(1000);
}