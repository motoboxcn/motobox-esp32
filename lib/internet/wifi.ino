#include <WiFi.h>

// WiFi设置
const char* ssid = "xiaomi-5-505";
const char* password = "mkonjibhu";


void initWifi()
{
    Serial.println("Connecting to WiFi network: " + String(ssid));
    WiFi.begin(ssid, password);
    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        count ++;
        delay(500);
        Serial.print(".");
        ui_wifi_connect_off();
        if (count > 100)
        {
            break;
        }
    }
    char ip[16];
    sprintf(ip, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
    ui_wifi_connect_on(ip);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
