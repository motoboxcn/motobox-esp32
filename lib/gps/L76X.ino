#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <dashboard.ino>

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
    // fmt GPS date as YYYY-MM-DD HH:MM:SS
    sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
    ui_time_update(date);
    Serial.printf("date: %s\t", date);
  }
  else{
    ui_time_update("1992-03-01 00:00:00");
  }
  // speed
  if (gps.speed.isValid())
  {
    static int speed = 0;
    speed = gps.speed.kmph();
    speed_dashboard(speed);
    Serial.printf("speed: %d\t", speed);
  }
  else
  {
    speed_dashboard(0);
  }

  // location
  if (gps.location.isValid())
  {
    char location[64];
    sprintf(location, "%f,%f", gps.location.lat(), gps.location.lng());
    lv_label_set_text(ui_suzhou, location);
    Serial.printf("location: %s\t", location);
  }
  
  // course to int
  if (gps.course.isValid())
  {
    char course[20];
    sprintf(course, "%.f", gps.course.deg());
    lv_label_set_text(ui_handingText, course);
    Serial.printf("course: %s\t", course);
  }
  else
  {
    lv_label_set_text(ui_handingText, "0");
  }
  // altitude
  if (gps.altitude.isValid())
  {
    char altitude[20];
    sprintf(altitude, "%.f", gps.altitude.meters());
    lv_label_set_text(ui_altitudeText, altitude);
    Serial.printf("altitude: %s\t", altitude);
  }
  else
  {
    lv_label_set_text(ui_altitudeText, "0");
  }
  // satellites
  if (gps.satellites.isValid())
  {
    char satellites[20];
    sprintf(satellites, "%d", gps.satellites.value());
    Serial.printf("satellites: %s\t", satellites);
    // lv_label_set_text(ui_satellitesText, satellites);
  }
  else
  {
    // lv_label_set_text(ui_satellitesText, "0");
  }
  // hdop
  if (gps.hdop.isValid())
  {
    char hdop[20];
    sprintf(hdop, "%.f", gps.hdop.value());
    Serial.printf("hdop: %s\t", hdop);
    // lv_label_set_text(ui_hdopText, hdop);
  }
  else
  {
    // lv_label_set_text(ui_hdopText, "0");
  }
  Serial.println();
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
  // xTaskCreate(LoopL76X, "LoopL76X", 1024, NULL, 5, NULL);
}
