#include <gy91.ino>
#include <lvgl.h>
#include <TaskScheduler.h>
#include <L76X.ino>
// #include <wifi.ino>

// 创建任务调度器对象
Scheduler taskScheduler;
Task t1(20, TASK_FOREVER, &loop_gy91);
Task t2(1000, TASK_FOREVER, &LoopL76X);

void setup()
{
  Serial.begin(115200);
  dashboardInit();
  setupGy91();
  setupL76X();
  // setupWifi();
  taskScheduler.init();
  taskScheduler.addTask(t1);
  taskScheduler.addTask(t2);
  taskScheduler.enableAll();
  Serial.println("Setup done");
}

void loop()
{
  taskScheduler.execute();
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}