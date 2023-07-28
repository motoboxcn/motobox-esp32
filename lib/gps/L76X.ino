#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 22, TXPin = 23;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void displayInfo()
{
  // time&date
  if (gps.date.isValid())
  {
    char date[20];
    sprintf(date, "%d-%d-%d %d:%d:%d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
    ui_time_update(date);
  }
  else{
    ui_time_update("00-00-00 00:00:00");
  }
  // speed
  if (gps.speed.isValid())
  {
    speed_dashboard(gps.speed.kmph());
  }
  else
  {
    speed_dashboard(0);
  }
  // location
  if (gps.location.isValid())
  {
    char location[20];
    sprintf(location, "%f,%f", gps.location.lat(), gps.location.lng());
    lv_label_set_text(ui_suzhou, location);
  }
  else
  {
    lv_label_set_text(ui_suzhou, "0,0");
  }
  // course
  if (gps.course.isValid())
  {
    char course[20];
    sprintf(course, "%f", gps.course.deg());
    lv_label_set_text(ui_handingText, course);
  }
  else
  {
    lv_label_set_text(ui_handingText, "0");
  }
  // altitude
  if (gps.altitude.isValid())
  {
    char altitude[20];
    sprintf(altitude, "%f", gps.altitude.meters());
    lv_label_set_text(ui_altitudeText, altitude);
  }
  else
  {
    lv_label_set_text(ui_altitudeText, "0");
  }
}

void LoopL76X()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true)
      ;
  }
}

void setupL76X()
{
  // 串口通信初始化
  ss.begin(GPSBaud);
  Serial.println("ESP32 with GPS is set up!");
  // xTaskCreate(LoopL76X, "LoopL76X", 1024*512, NULL, 1, NULL);
}
