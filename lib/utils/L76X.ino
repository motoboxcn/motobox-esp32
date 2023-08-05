#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ui.h>
#include <dashboard.ino>

static const int RXPin = 20, TXPin = 19;
static const uint32_t GPSBaud = 9600;

char *location;

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
    // Convert gpstime to local time
    time_t gpstime = gps.time.value();
    struct tm* timeinfo;
    // Set the timezone to Beijing  
    setenv("TZ", "Asia/Shanghai", 1);
    tzset();
    // Convert gpstime to local time in Beijing
    timeinfo = localtime(&gpstime);
    // Format the date and time as desired
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", timeinfo);
    ui_time_update(date);
  }
  else
  {
    ui_time_update("1992-03-01 00:00:00");
  }
  // speed
  if (gps.speed.isValid())
  {
    static int speed = 0;
    speed = gps.speed.kmph();
    speed_dashboard(speed);
  }
  else
  {
    speed_dashboard(0);
  }

  // location
  if (gps.location.isValid())
  {
    sprintf(location, "%.6f,%.6f", gps.location.lat(), gps.location.lng());
    lv_label_set_text(ui_gpsText, location);
    Serial.println(location);
  }

  // course to int
  if (gps.course.isValid())
  {
    char course[20];
    sprintf(course, "%.f", gps.course.deg());
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
    sprintf(altitude, "%.f", gps.altitude.meters());
    lv_label_set_text(ui_altitudeText, altitude);
  }
  else
  {
    lv_label_set_text(ui_altitudeText, "0");
  }
  // satellites 是一个在 GPS 定位中常用的术语，表示可见的卫星数量。在 GPS 接收器中，通过接收卫星发出的信号来确定位置。satellites 变量通常用于记录当前可见卫星的数量。通过跟踪更多的卫星，可以提高 GPS 定位的精度和可靠性。
  if (gps.satellites.isValid())
  {
    char satellites[20];
    sprintf(satellites, "%d", gps.satellites.value());
    lv_label_set_text(ui_gpsNuText, satellites);
  }
  else
  {
    // lv_label_set_text(ui_satellitesText, "0");
  }
  // HDOP (Horizontal Dilution of Precision) 是一种用于衡量 GPS 位置精度的指标。它是通过衡量接收器在计算位置时的卫星几何分布来计算的。HDOP 值越小，表示接收器的位置精度越高。一般来说，较低的 HDOP 值表示较高的精度，较高的 HDOP 值表示较低的精度。HDOP 值通常在范围 0 到 10 之间，较理想的值是小于等于 1。
  if (gps.hdop.isValid())
  {
    char hdop[20];
    sprintf(hdop, "%.f", gps.hdop.value());
    lv_label_set_text(ui_hdopNuText, hdop);
    // lv_label_set_text(ui_hdopText, hdop);
  }
  else
  {
    // lv_label_set_text(ui_hdopText, "0");
  }
}

void LoopL76X()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
  if (millis() > 5000 && gps.charsProcessed() < 10) // if we don't hear from the GPS for 5 seconds, send an error message
  {
    Serial.println(F("No GPS detected: check wiring."));
  }
  Serial.println(F("Done"));
}

void setupL76X()
{
  // 串口通信初始化
  ss.begin(GPSBaud);
  Serial.println("ESP32 with GPS is set up!");
}
