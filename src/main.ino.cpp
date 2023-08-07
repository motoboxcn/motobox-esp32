# 1 "/var/folders/28/z1jd9trj1xv9ffjy7b6x0wf80000gp/T/tmpfpo5q7pe"
#include <Arduino.h>
# 1 "/Users/zhoushoujian/github/motobox-esp32/src/main.ino"
#include <gy91.ino>
#include <lvgl.h>
#include <TaskScheduler.h>
#include <L76X.ino>



Scheduler taskScheduler;
void setup();
void loop();
#line 9 "/Users/zhoushoujian/github/motobox-esp32/src/main.ino"
Task t1(20, TASK_FOREVER, &loop_gy91_mid);
Task t2(0, TASK_FOREVER, &LoopL76X);

void setup()
{
  Serial.begin(115200);
  dashboardInit();
  setupGy91();
  setupL76X();

  taskScheduler.init();
  taskScheduler.addTask(t1);
  taskScheduler.addTask(t2);
  taskScheduler.enableAll();
  Serial.println("Setup done");
}

void loop()
{
  taskScheduler.execute();

}