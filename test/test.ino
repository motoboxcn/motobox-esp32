#include <HardwareSerial.h>
#include <TinyGPS++.h>

HardwareSerial gpsSerial(1);
TinyGPSPlus gps;

void setup()
{
    Serial.begin(115200);
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // RX pin: 16, TX pin: 17
}

void loop()
{
    while (gpsSerial.available() > 0)
    {
        if (gps.encode(gpsSerial.read()))
        {
            if (gps.location.isValid())
            {
                Serial.print("Lat: ");
                Serial.print(gps.location.lat(), 6);
                Serial.print(" Long: ");
                Serial.println(gps.location.lng(), 6);
            }
        }
    }
}