#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include "ble.ino"
#include "../ui/ui.h"

#define SDA_PIN 19 // 0x68
#define SCL_PIN 18 // 0x69

#define BMP_ENABLED 0

MPU9250_asukiaaa mpu;

#if BMP_ENABLED
Adafruit_BMP280 bmp;
#endif

float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setupGy91()
{
  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);
  mpu.beginAccel(); // 初始化加速度计
  // mpu.beginGyro();  // 初始化陀螺仪
  // mpu.beginMag();   // 初始化磁力计

#if BMP_ENABLED
  Serial.println("start Adafruit_BMP280");
  bmp.begin();
  Serial.println("done Adafruit_BMP280");
#endif
}

float roll, pitch, yaw;

// 定义平均滤波数组大小
#define FILTER_SIZE 32     // 缓冲区大小 ,32差不多，128 延迟大
float buffer[FILTER_SIZE]; // 缓冲区
int roll_index = 0;        // 缓冲区索引

// 添加新数据到缓冲区中
void addData(float newData)
{
  buffer[roll_index] = newData;
  // 循环更新缓冲区索引
  roll_index = (roll_index + 1) % FILTER_SIZE;
}

// 计算平均值
float getFilteredData()
{
  float average = 0;
  for (int i = 0; i < FILTER_SIZE; i++)
  {
    average += buffer[i];
  }
  return average / FILTER_SIZE;
}

void bleSendGYRO(float filteredData)
{
  NimBLEService *pSvc = pServer->getServiceByUUID(GYRO_SERVICE_UUID);
  if (pSvc)
  {
    NimBLECharacteristic *pChr = pSvc->getCharacteristic(GYRO_CHARACTERISTIC_UUID);
    pChr->setValue(String(filteredData));
    if (pChr)
    {
      pChr->notify(true);
    }
  }
}

void main_loop_gy91()
{
  // 更新传感器数据
  mpu.accelUpdate(); // 更新加速度计数据
  aX = mpu.accelX();
  aY = mpu.accelY();
  aZ = mpu.accelZ();
  roll = atan(aY / sqrt(aX * aX + aZ * aZ)) * 180.0 / PI;
  // 进行平均滤波
  addData(roll);                          // 将数据放入缓冲区
  float filteredData = getFilteredData(); // 获取平均值作为最终数据

#if ENABLE_BLE
  bleSendGYRO(filteredData);
#endif
  // 更新UI和其他操作
  lv_img_set_angle(ui_roll, filteredData * 10);
  lv_label_set_text_fmt(ui_rollText, "%d°", int(filteredData));
}