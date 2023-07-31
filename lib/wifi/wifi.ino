#include <WiFi.h>

static const char ssid[] = "mikas iPhone";
static const char password[] = "11111111";

void initWifi()
{
    Serial.println("Connecting to WiFi network: " + String(ssid));
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
}

void loopWifi(void *pvParameters)
{
    while (1)
    {
        Serial.println("WiFi status: " + String(WiFi.status()));
        delay(1000);
    }
}

void setupWifi()
{
    initWifi();
    xTaskCreate(loopWifi, "loop_wifi", 1024*2, NULL, 1, NULL);
}
