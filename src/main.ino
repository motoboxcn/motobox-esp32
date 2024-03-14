#include <TaskScheduler.h>
#include "core/dashboard.ino"
#include "core/gy91.ino"
#include "core/gps_l76x.ino"

// 创建任务调度器对象,任务执行必须是瞬时的，不能阻塞
Scheduler taskScheduler;

#define USE_DEMON 1   // 1开启 0关闭，是否模拟仪表变化
#define ENABLE_GY91 1 // 1开启 0关闭，是否开启陀螺仪
#define ENABLE_L76X 1 // 1开启 0关闭，是否开启L76X
#define ENABLE_WIFI 0 // 1开启 0关闭，是否开启wifi

#if USE_DEMON
Task t1(200, TASK_FOREVER, &speed_demon_task);
#endif

#if ENABLE_GY91
Task t2(100, TASK_FOREVER, &loop_gy91);
#endif

#if ENABLE_L76X
Task t3(2000, TASK_FOREVER, &loop_l76x);
#endif

void setup()
{
  Serial.begin(115200);
  // 初始化函数TFT仪表驱动和LVGL
  LVSetup();
  // 初始化UI图形
  ui_init();
  // 展示开机仪表动画
  ShowSpeed();

  taskScheduler.init();
#if USE_DEMON
  taskScheduler.addTask(t1);
  Serial.println("add task speedDemonTask success.");
#endif

#if ENABLE_GY91
  setupGy91();
  taskScheduler.addTask(t2);
  Serial.println("add task gy91Task success.");
#endif

#if ENABLE_L76X
  setupL76X();
  taskScheduler.addTask(t3);
  Serial.println("add task l76xTask success.");
#endif

  taskScheduler.enableAll();
}

void loop()
{
  taskScheduler.execute();
  delay(5);
  lv_timer_handler();
  lv_tick_inc(5);
}