#include <TinyGPSPlus.h>
#include "../ui/ui.h"
// #include <SoftwareSerial.h>

// static const int RXPin = 20, TXPin = 19;

// char location[20]; // Allocate memory for the location variable

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
// SoftwareSerial ss(RXPin, TXPin);

void setupL76X()
{
  Serial.print(F("Testing TinyGPSPlus library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println("ESP32 with GPS is set up!");
}

void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    lv_label_set_text_fmt(ui_localtionText, "%f,%f", gps.location.lat(), gps.location.lng());
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid() && gps.time.isValid())
  {
    // time 1992-03-01 12:34:56
    lv_label_set_text_fmt(ui_gpsTime, "%4d-%2d-%2d %2d:%2d:%2d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
    Serial.printf("%4d-%2d-%2d %2d:%2d:%2d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
  }
  else
  {
    Serial.print(F("DATE INVALID"));
  }

  Serial.println();
}

void loop_l76x()
{
  const char *gpsStream =
      "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
      "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
      "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
      "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
      "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
      "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";
  while (*gpsStream)
    if (gps.encode(*gpsStream++))
      displayInfo();
}