#include <TaskScheduler.h>
#include "core/dashboard.ino"
#include "core/gy91.ino"
// #include <L76X.ino>
// #include <wifi.ino>

// 创建任务调度器对象,任务执行必须是瞬时的，不能阻塞
Scheduler taskScheduler;

#define USE_DEMON 0   // 1开启 0关闭，是否模拟仪表变化
#define ENABLE_GY91 1 // 1开启 0关闭，是否开启陀螺仪

#if USE_DEMON
Task t1(0, TASK_FOREVER, &speed_demon);
#else
Task t1(0, TASK_FOREVER, &speed_demon_task);
#endif

#if ENABLE_GY91
Task t2(0, TASK_FOREVER, &loop_gy91);
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
#endif

#if ENABLE_GY91
  setupGy91();
  taskScheduler.addTask(t2);
  Serial.println("add task gy91Task success.");
#endif

  // taskScheduler.enableAll();
  t1.enable();
  t2.enable();
}

void loop()
{
  taskScheduler.execute();
  delay(5);
  lv_timer_handler();
  lv_tick_inc(5);
}