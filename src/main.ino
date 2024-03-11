// #include <gy91.ino>
#include <lvgl.h>
#include <TaskScheduler.h>
#include "core/dashboard.ino"
// #include <L76X.ino>
// #include <wifi.ino>

// 创建任务调度器对象
// Scheduler taskScheduler;
// Task t1(20, TASK_FOREVER, &loop_gy91_mid);
// Task t2(0, TASK_FOREVER, &LoopL76X);

void setup()
{
  Serial.begin(115200);
  // 初始化函数TFT仪表驱动和LVGL
  LVSetup();

  // 初始化UI图形
  ui_init();

  // 展示开机仪表动画
  ShowSpeed();

  // setupGy91();
  // setupL76X();
  // setupWifi();
  // taskScheduler.init();
  // taskScheduler.addTask(t1);
  // taskScheduler.enableAll();
}

void loop()
{
  // taskScheduler.execute();
  Serial.println("Loop");
  delay(1000);
}