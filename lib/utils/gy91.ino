#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <ui.h>

MPU9250_asukiaaa mpu;
Adafruit_BMP280 bmp;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection;
float roll, pitch;
float magX, magY, magZ;

#define SDA_PIN 17  // 0x68
#define SCL_PIN 18  // 0x69

// 定义全局变量
const int numReadings = 20;  // 用于计算移动平均的读数数量
float rollReadings[numReadings];  // 存储roll读数的数组
int rollIndex = 0;  // 当前读数的索引
float rollTotal = 0;  // roll读数的总和
// 平均滤波
void loop_gy91()
{
    // 更新传感器数据
    mpu.accelUpdate(); // 更新加速度计数据
    aX = mpu.accelX();
    aY = mpu.accelY();
    aZ = mpu.accelZ();
    roll = atan(aY / sqrt(aX * aX + aZ * aZ)) * 180.0 / PI;

    // 计算移动平均
    rollTotal = rollTotal - rollReadings[rollIndex];  // 减去最旧的读数
    rollReadings[rollIndex] = roll;  // 存储最新的读数
    rollTotal = rollTotal + rollReadings[rollIndex];  // 加上最新的读数
    rollIndex = (rollIndex + 1) % numReadings;  // 更新索引

    // 计算平均值
    float rollAverage = rollTotal / numReadings;

    // 降低灵敏度
    float sensitivity = 1;  // 设置灵敏度，可以根据需要进行调整
    rollAverage = rollAverage * sensitivity;
    // Serial.printf("rollAverage: %f\t", rollAverage);

    // 更新UI和其他操作
    lv_img_set_angle(ui_roll, rollAverage * 10);
    lv_label_set_text_fmt(ui_rollText, "%d°", int(rollAverage));
    lv_timer_handler();
}

// 中值滤波
void loop_gy91_mid() {
  // 更新传感器数据
  mpu.accelUpdate(); // 更新加速度计数据
  aX = mpu.accelX();
  aY = mpu.accelY();
  aZ = mpu.accelZ();
  roll = atan(aY / sqrt(aX * aX + aZ * aZ)) * 180.0 / PI;

  // 使用中值滤波器计算平均值
  rollReadings[rollIndex] = roll;  // 存储最新的读数
  rollIndex = (rollIndex + 1) % numReadings;  // 更新索引

  // 排序读数数组
  for (int i = 0; i < numReadings - 1; i++) {
    for (int j = i + 1; j < numReadings; j++) {
      if (rollReadings[j] < rollReadings[i]) {
        float temp = rollReadings[i];
        rollReadings[i] = rollReadings[j];
        rollReadings[j] = temp;
      }
    }
  }

  // 计算中值
  float rollMedian = rollReadings[numReadings / 2];

  // 降低灵敏度
  float sensitivity = 1;  // 设置灵敏度，可以根据需要进行调整
  rollMedian = rollMedian * sensitivity;
  // Serial.print("rollMedian: ");
  // Serial.print(rollMedian);
  // Serial.print("\t");
  // Serial.println();


  // 更新UI和其他操作
  lv_img_set_angle(ui_roll, rollMedian * 10);
  lv_label_set_text_fmt(ui_rollText, "%d° ", int(rollMedian));
  lv_timer_handler();
}

void setupGy91()
{
    Wire.begin(SDA_PIN, SCL_PIN);
    mpu.setWire(&Wire);
    mpu.beginAccel();
    mpu.beginGyro();
    mpu.beginMag();
    bmp.begin();
}
