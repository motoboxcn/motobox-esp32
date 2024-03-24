#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "ble.ino"
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

const char *printfTime(TinyGPSPlus gps)
{
  static char time[20];
  sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d",
          gps.date.year(), gps.date.month(), gps.date.day(),
          gps.time.hour(), gps.time.minute(), gps.time.second());
  return time;
}

const char *printfCourse(float course)
{
  return gps.cardinal(course);
}

double lat;
double lng;
double gps_speed;
double gps_altitude;
int gps_satellites;
double gps_course;
String gps_course_string = "N";

// 无延迟的循环获取
void main_loop_l76x()
{
#if EnableGPS
  while (gpsSerial.available() > 0)
  {
    if (gps.encode(gpsSerial.read()))
    {
      if (gps.location.isValid())
      {
        lat = gps.location.lat();
        lng = gps.location.lng();
      }
      else
      {
        lat = 0;
        lng = 0;
      }

      if (gps.speed.isValid())
      {
        gps_speed = gps.speed.kmph();
      }
      else
      {
        gps_speed = 0;
      }

      if (gps.altitude.isValid())
      {
        gps_altitude = gps.altitude.meters();
      }
      else
      {
        gps_altitude = 0;
      }

      if (gps.course.isValid())
      {
        gps_course = gps.course.deg();
        gps_course_string = printfCourse(gps_course);
      }
      else
      {
        gps_course = -1;
        gps_course_string = "-";
      }

      if (gps.satellites.isValid())
      {
        gps_satellites = gps.satellites.value();
      }
      else
      {
        gps_satellites = -1;
      }
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

void displayInfo()
{
  // Time
  if (gps.date.isValid() && gps.time.isValid())
  {
    lv_label_set_text_fmt(ui_gpsTime, "%s", printfTime(gps));
  }

  // Location
  if (gps.location.isValid())
  {
    lv_label_set_text_fmt(ui_gpsText, "%s, %s", String(lat, 6), String(lng, 6));
  }

  if (gps.speed.isValid())
  {
    speed_dashboard_without_time(gps_speed);
  }
  else
  {
    lv_label_set_text_fmt(ui_speedText, "---");
  }

  if (gps.altitude.isValid())
  {
    lv_label_set_text_fmt(ui_altitudeText, "%sm", String(gps_altitude, 1));
  }
  else
  {
    lv_label_set_text_fmt(ui_altitudeText, "---");
  }

  if (gps.course.isValid())
  {
    lv_label_set_text_fmt(ui_courseText, "%s", gps_course_string);
    lv_img_set_angle(ui_course, gps_course * 10);
  }
  else
  {
    lv_label_set_text_fmt(ui_courseText, "---");
  }

  if (gps.satellites.isValid())
  {
    lv_label_set_text_fmt(ui_satellitesText, "%d", gps_satellites);
  }
  else
  {
    lv_label_set_text_fmt(ui_satellitesText, "--");
  }
}

void bleSendGPS()
{
  NimBLEService *pSvc = pServer->getServiceByUUID(GPS_SERVICE_UUID);
  if (pSvc)
  {
    NimBLECharacteristic *pChr = pSvc->getCharacteristic(GPS_CHARACTERISTIC_UUID);
    String GYROVALUES =
        String(printfTime(gps)) + "," + String(lat, 6) + "," + String(lng, 6) + "," + String(gps_speed) + "," +
        String(gps_altitude) + "," + String(gps_course) + "," + String(gps_course_string) + "," + String(gps_satellites);
    pChr->setValue(GYROVALUES);
    if (pChr)
    {
      pChr->notify(true);
    }
    Serial.print("BLE GPS Send ");
    Serial.println(GYROVALUES);
  }
}

void loop_l76x()
{
  displayInfo();
#if ENABLE_BLE
  bleSendGPS();
#endif
}