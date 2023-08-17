#include <gy91.ino>
#include <lvgl.h>
#include <TaskScheduler.h>
#include <L76X.ino>
// #include <iot.ino>
#include <exmq.ino>

// 创建任务调度器对象
Scheduler taskScheduler;
Task t1(20, TASK_FOREVER, &loop_gy91_mid);
Task t2(0, TASK_FOREVER, &LoopL76X);
// Task t3(0, TASK_FOREVER, &loopIot);
Task t3(2000, TASK_FOREVER, &loopExMq);

void setup()
{
  Serial.begin(115200);
  dashboardInit();
  setupGy91();
  setupL76X();
  // setupIot();
  setupExMq();
  taskScheduler.init();
  taskScheduler.addTask(t1);
  taskScheduler.addTask(t2);
  taskScheduler.addTask(t3);
  taskScheduler.enableAll();
  Serial.println("Setup done");
}

void loop()
{
  taskScheduler.execute();
  // LoopL76X();
}