#define ENABLE_BLE 1  // 1开启 0关闭，是否开启BLE
#define ENABLE_GY91 1 // 1开启 0关闭，是否开启陀螺仪
#define ENABLE_L76X 1 // 1开启 0关闭，是否开启L76X
#define USE_TFT 0     // 1开启 0关闭，是否开启TFT显示屏
#define USE_DEMON 0   // 1开启 0关闭，是否模拟仪表变化

#include "core/dashboard.ino"
#include <TaskScheduler.h>
#include "sensor/gy91.ino"
#include "sensor/gps_l76x.ino"

// 创建任务调度器对象,任务执行必须是瞬时的，不能阻塞
Scheduler taskScheduler;

#if USE_TFT
#if USE_DEMON
Task t1(200, TASK_FOREVER, &speed_demon_task);
#endif
#endif

#if ENABLE_L76X
Task t2(250, TASK_FOREVER, &loop_l76x); // 任务执行时间间隔必须是 0 连续的，否则库解析字符串数据会出错
#endif

#if ENABLE_GY91
Task t3(100, TASK_FOREVER, &loop_gy91);
#endif

void setup()
{
  Serial.begin(115200);
  taskScheduler.init();

#if USE_TFT
  // 初始化函数TFT仪表驱动和LVGL
  LVSetup();
  // 初始化UI图形
  ui_init();
  // 展示开机仪表动画
  ShowSpeed();
#if USE_DEMON
  taskScheduler.addTask(t1);
  Serial.println("add task speedDemonTask success.");
#endif
#endif

#if ENABLE_BLE
  setupBLE();
#endif

#if ENABLE_GY91
  setupGy91();
  taskScheduler.addTask(t3);
  Serial.println("add task gy91Task success.");
#endif

#if ENABLE_L76X
  setupL76X();
  taskScheduler.addTask(t2);
  Serial.println("add task l76xTask success.");
#endif

  taskScheduler.enableAll();
  Serial.println("taskScheduler enableAll success.");
}

void loop()
{
  taskScheduler.execute();
#if ENABLE_L76X
  main_loop_l76x();
#endif
  delay(5);

  if (USE_TFT)
  {
    lv_timer_handler();
    lv_tick_inc(5);
  }
}