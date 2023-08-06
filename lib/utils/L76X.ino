#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ui.h>
#include <dashboard.ino>

static const int RXPin = 20, TXPin = 19;
static const uint32_t GPSBaud = 9600;

char location[20]; // Allocate memory for the location variable

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setupL76X()
{
  ss.begin(GPSBaud);
  Serial.println("ESP32 with GPS is set up!");
}

void displayInfo()
{
  char date[20];
  Serial.print("GPS time: ");
  // 将日期和时间转换为字符串
  String year = String(gps.date.year()) ? String(gps.date.year()) : "1992";
  String month = String(gps.date.month()) ? String(gps.date.month()) : "03";
  String day = String(gps.date.day()) ? String(gps.date.day()) : "01";
  String hour = String(gps.time.hour()) ? String(gps.time.hour()) : "00";
  String minute = String(gps.time.minute()) ? String(gps.time.minute()) : "00";
  String second = String(gps.time.second()) ? String(gps.time.second()) : "00";
  // 格式化日期和时间字符串
  snprintf(date, sizeof(date), "%04s-%02s-%02s %02s:%02s:%02s", year.c_str(), month.c_str(), day.c_str(), hour.c_str(), minute.c_str(), second.c_str());

  // 打印日期和时间
  Serial.println(date);
  ui_time_update(date);

  // speed
  char speed[20];
  double speedGPS = gps.speed.kmph() ? gps.speed.kmph() : 0.0;
  speed_dashboard(speedGPS);

  // location
  if (gps.location.isValid())
  {
    sprintf(location, "%.6f,%.6f", gps.location.lat(), gps.location.lng());
    lv_label_set_text(ui_gpsText, location);
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
    lv_label_set_text(ui_gpsNuText, "0");
  }
  // HDOP (Horizontal Dilution of Precision) 是一种用于衡量 GPS 位置精度的指标。它是通过衡量接收器在计算位置时的卫星几何分布来计算的。HDOP 值越小，表示接收器的位置精度越高。一般来说，较低的 HDOP 值表示较高的精度，较高的 HDOP 值表示较低的精度。HDOP 值通常在范围 0 到 10 之间，较理想的值是小于等于 1。
  if (gps.hdop.isValid())
  {
    char hdop[20];
    sprintf(hdop, "%.f", gps.hdop.value());
    lv_label_set_text(ui_hdopNuText, hdop);
  }
  else
  {
    lv_label_set_text(ui_hdopNuText, "0");
  }
}

void LoopL76X()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      displayInfo();
      lv_timer_handler();
    }
  // else
  // {
  //   Serial.println(ss.readStringUntil('\n'));
  // }

  if (millis() > 5000 && gps.charsProcessed() < 10) // if we don't hear from the GPS for 5 seconds, send an error message
  {
    Serial.println(F("No GPS detected: check wiring.\n"));
  }
}