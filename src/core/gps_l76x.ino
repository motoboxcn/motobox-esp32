#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "../ui/ui.h"
// 不能加入到 taskScheduler 中，否则会阻塞任务调度导致获取 GPS 串口数据不全

#define EnableGPS 1

#if EnableGPS
SoftwareSerial gpsSerial(22, 23); // RX, TX
#endif

// The TinyGPSPlus object
TinyGPSPlus gps;

void setupL76X()
{
  Serial.print(F("Testing TinyGPSPlus library v. "));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println("ESP32 with GPS is set up!");
#if EnableGPS
  gpsSerial.begin(9600);
#endif
}

const char *printfLocation(float lat, float lng)
{
  static char location[20];
  sprintf(location, "%3.6f\n%3.6f", lat, lng);
  return location;
}

const char *printfTime(TinyGPSPlus gps)
{
  static char time[20];
  sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d",
          gps.date.year(), gps.date.month(), gps.date.day(),
          gps.time.hour(), gps.time.minute(), gps.time.second());
  return time;
}

// 获取GMT时区时间并转换为本地时区
const char *printfLocalTime(TinyGPSPlus gps)
{
  struct tm t;

  t.tm_year = gps.date.year() - 1900;
  t.tm_mon = gps.date.month() - 1;
  t.tm_mday = gps.date.day();
  t.tm_hour = gps.time.hour();
  t.tm_min = gps.time.minute();
  t.tm_sec = gps.time.second();
  t.tm_isdst = -1; // Is DST on? 1 = yes, 0 = no, -1 = unknown

  // convert GMT time to local time
  time_t localTime = mktime(&t);

  // 时间格式为 "%04d-%02d-%02d %02d:%02d:%02d"
  static char time[20];
  strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&localTime));
  return time;
}

const char *printfSpeed(float speed)
{
  static char speedText[20];
  sprintf(speedText, "%.0f", speed);
  return speedText;
}

const char *printfAltitude(float altitude)
{
  static char altitudeText[20];
  sprintf(altitudeText, "%.0fm", altitude);
  return altitudeText;
}

const char *printfCourse(float course)
{
  return gps.cardinal(gps.course.deg());
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    lv_label_set_text_fmt(ui_gpsText, "%s", printfLocation(gps.location.lat(), gps.location.lng()));
  }

  if (gps.date.isValid() && gps.time.isValid())
  {
    lv_label_set_text_fmt(ui_gpsTime, "%s", printfLocalTime(gps));
  }

  if (gps.speed.isValid())
  {
    lv_label_set_text_fmt(ui_speedText, "%s", printfSpeed(gps.speed.kmph()));
  }
  else
  {
    lv_label_set_text_fmt(ui_speedText, "---");
  }

  if (gps.altitude.isValid())
  {
    lv_label_set_text_fmt(ui_altitudeText, "%s", printfAltitude(gps.altitude.meters()));
  }
  else
  {
    lv_label_set_text_fmt(ui_altitudeText, "---");
  }

  if (gps.course.isValid())
  {
    lv_label_set_text_fmt(ui_courseText, "%s", printfCourse(gps.course.deg()));
    lv_img_set_angle(ui_course, gps.course.deg() * 10);
  }
  else
  {
    lv_label_set_text_fmt(ui_courseText, "---");
  }

  if (gps.satellites.isValid())
  {
    lv_label_set_text_fmt(ui_satellitesText, "%d", gps.satellites.value());
  }
  else
  {
    lv_label_set_text_fmt(ui_satellitesText, "--");
  }
}

void loop_l76x()
{
#if EnableGPS
  while (gpsSerial.available() > 0)
  {
    if (gps.encode(gpsSerial.read()))
    {
      displayInfo();
    }
  }
#else
  const char *gpsStream =
      "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
      "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
      "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
      "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
      "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
      "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";
  while (*gpsStream)
    if (gps.encode(*gpsStream++))
    {
      displayInfo();
    }
#endif
}