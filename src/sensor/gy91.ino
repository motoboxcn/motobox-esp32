#include <MPU9250_asukiaaa.h>
#include "ble.ino"
#include "../ui/ui.h"

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;

float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ;

void setupGy91()
{
#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif
  mySensor.beginAccel(); // 初始化加速度计
  mySensor.beginGyro();  // 初始化陀螺仪
  mySensor.beginMag();   // 初始化磁力计

  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
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
  uint8_t sensorId;
  int result;

  result = mySensor.readId(&sensorId);
  if (result == 0)
  {
    Serial.println("sensorId: " + String(sensorId));
  }
  else
  {
    Serial.println("Cannot read sensorId " + String(result));
  }

  result = mySensor.accelUpdate();
  if (result == 0)
  {
    mySensor.accelUpdate(); // 更新加速度计数据
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    roll = atan(aY / sqrt(aX * aX + aZ * aZ)) * 180.0 / PI;
    // 进行平均滤波
    addData(roll);                          // 将数据放入缓冲区
    float filteredData = getFilteredData(); // 获取平均值作为最终数据
#if ENABLE_BLE
    bleSendGYRO(filteredData);
#endif
    // 更新UI和其他操作
#if USE_TFT
    lv_img_set_angle(ui_roll, filteredData * 10);
    lv_label_set_text_fmt(ui_rollText, "%d°", int(filteredData));
#endif
    Serial.println("accelX: " + String(aX));
    Serial.println("accelY: " + String(aY));
    Serial.println("accelZ: " + String(aZ));
    Serial.println("accelSqrt: " + String(aSqrt));
  }
  else
  {
    Serial.println("Cannod read accel values " + String(result));
  }

  result = mySensor.gyroUpdate();
  if (result == 0)
  {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    gZ = mySensor.gyroZ();
    Serial.println("gyroX: " + String(gX));
    Serial.println("gyroY: " + String(gY));
    Serial.println("gyroZ: " + String(gZ));
  }
  else
  {
    Serial.println("Cannot read gyro values " + String(result));
  }

  result = mySensor.magUpdate(); // 更新磁力计数据
  if (result != 0)
  {
    Serial.println("cannot read mag so call begin again");
    mySensor.beginMag();
    result = mySensor.magUpdate();
  }
  if (result == 0)
  {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();
    Serial.println("magX: " + String(mX));
    Serial.println("maxY: " + String(mY));
    Serial.println("magZ: " + String(mZ));
    Serial.println("horizontal direction: " + String(mDirection));
  }
  else
  {
    Serial.println("Cannot read mag values " + String(result));
  }

  Serial.println("at " + String(millis()) + "ms");
  Serial.println(""); // Add an empty line
}
