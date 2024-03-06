#include <gy91.ino>
#include <lvgl.h>
#include <TaskScheduler.h>
#include <dashboard.ino>
// #include <L76X.ino>
// #include <wifi.ino>

// 创建任务调度器对象
Scheduler taskScheduler;
Task t1(20, TASK_FOREVER, &loop_gy91_mid);
// Task t2(0, TASK_FOREVER, &LoopL76X);

void setup()
{
  Serial.begin(115200);
  Serial.println("Start setup");
  dashboardInit();
  // setupGy91();
  // setupL76X();
  // setupWifi();
  taskScheduler.init();
  taskScheduler.addTask(t1);
  // taskScheduler.addTask(t2);
  // taskScheduler.enableAll();
  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler();
  taskScheduler.execute();
  // print gy91
  // Serial.println(bmp.readTemperature());
}