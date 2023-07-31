#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <ui.h>

MPU9250_asukiaaa mpu;
Adafruit_BMP280 bmp;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection;
float roll, pitch;
int mX, mY, mZ;

#define SDA_PIN 32  // 0x68
#define SCL_PIN 33  // 0x69

void loop_gy91()
{
    mpu.accelUpdate(); // 更新加速度计数据
    aX = mpu.accelX();
    aY = mpu.accelY();
    aZ = mpu.accelZ();
    // 设置 roll 变化范围为 0 ~ 180
    roll = atan(aY / sqrt(aX * aX + aZ * aZ)) * 180.0 / PI;
    pitch = atan(-aX / sqrt(aY * aY + aZ * aZ)) * 180.0 / PI;

    mpu.gyroUpdate(); // 更新陀螺仪数据
    gX = mpu.gyroX();
    gY = mpu.gyroY();
    gZ = mpu.gyroZ();

    mpu.magUpdate(); // 更新磁力计数据
    mX = mpu.magX();
    mY = mpu.magY();
    mZ = mpu.magZ();
    mDirection = atan2(mY, mX) * 180.0 / PI; // 磁力计方向

    // Serial.print("gyro: ");
    // Serial.print("\tX: " + String(gX));
    // Serial.print("\tY: " + String(gY));
    // Serial.print("\tZ: " + String(gZ));

    // Serial.print("\taccel: ");
    // Serial.print("\tX: " + String(aX));
    // Serial.print("\tY: " + String(aY));
    // Serial.print("\tZ: " + String(aZ));

    // Serial.print("\tmag: ");
    // Serial.print("\tX: " + String(mX));
    // Serial.print("\tY: " + String(mY));
    // Serial.print("\tZ: " + String(mZ));

    // Serial.print("\tmDirection: " + String(mDirection));
    
    // Serial.print("\troll: " + String(roll));
    // Serial.print("\tpitch: " + String(pitch));

    lv_img_set_angle(ui_motoRoll,roll*10);
    lv_label_set_text_fmt(ui_rollText, "%d°", int(roll));

    // Serial.print("\tTemperature(*C): ");
    // Serial.print(bmp.readTemperature());

    // Serial.print("\tPressure(Pa): ");
    // Serial.print(bmp.readPressure());

    // Serial.println("");
}

void loopGy91(void *pvParameters)
{
    for (;;)
    {
        loop_gy91();
        delay(100);
    }
}

void setupGy91()
{
    Wire.begin(SDA_PIN, SCL_PIN);
    mpu.setWire(&Wire);
    mpu.beginAccel();
    mpu.beginGyro();
    mpu.beginMag();
    bmp.begin();
    xTaskCreate(loopGy91, "loopGy91", 1024*2, NULL, 10, NULL);
}
