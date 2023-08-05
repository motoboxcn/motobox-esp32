#include <WiFi.h>
#include <ui.h>

static const char ssid[] = "mikas iPhone";
static const char password[] = "11111111";

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
void setupWifi()
{
    initWifi();
}
