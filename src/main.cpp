#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
MPU9250_asukiaaa mpu;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection;
uint16_t mX, mY, mZ;

#define SDA_PIN 32
#define SCL_PIN 25

void setup() {
  
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.setWire(&Wire);

  bmp.begin();
  mpu.beginAccel();
  mpu.beginGyro();
  mpu.beginMag();

}

void loop() {

  if (mpu.accelUpdate() == 0) {
    aX = mpu.accelX();
    aY = mpu.accelY();
    aZ = mpu.accelZ();
    aSqrt = mpu.accelSqrt();
    Serial.print("accelX: " + String(aX));
    Serial.print("\taccelY: " + String(aY));
    Serial.print("\taccelZ: " + String(aZ));
    Serial.print("\taccelSqrt: " + String(aSqrt));
  }

  if (mpu.gyroUpdate() == 0) {
    gX = mpu.gyroX();
    gY = mpu.gyroY();
    gZ = mpu.gyroZ();
    Serial.print("\tgyroX: " + String(gX));
    Serial.print("\tgyroY: " + String(gY));
    Serial.print("\tgyroZ: " + String(gZ));
  }

  if (mpu.magUpdate() == 0) {
    mX = mpu.magX();
    mY = mpu.magY();
    mZ = mpu.magZ();
    mDirection = mpu.magHorizDirection();
    Serial.print("\tmagX: " + String(mX));
    Serial.print("\tmaxY: " + String(mY));
    Serial.print("\tmagZ: " + String(mZ));
    Serial.print("\thorizontalDirection: " + String(mDirection));
  }

  Serial.print("\tTemperature(*C): ");
  Serial.print(bmp.readTemperature());

  Serial.print("\tPressure(Pa): ");
  Serial.print(bmp.readPressure());

  Serial.println("");
  delay(50);
  }