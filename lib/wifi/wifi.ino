#include <WiFi.h>
#include <HTTPClient.h>

static const char ssid[] = "mikas iPhone";
static const char password[] = "11111111";
const String apiKey = "8c9bc9387871a3a487383c97235b81ed";

HTTPClient client;

void initWifi()
{
    Serial.println("Connecting to WiFi network: " + String(ssid));
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        ui_wifi_connect_off();
    }
    char ip[16];
    sprintf(ip, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
    ui_wifi_connect_on(ip);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

// get amap location
void getAmapLocation()
{
    // restapi.amap.com/v3/geocode/regeo?key=您的key&location=116.481488,39.990464&poitype=商务写字楼&radius=1000&extensions=all&batch=false&roadlevel=0
    String url = "http://restapi.amap.com/v3/geocode/regeo?key=" + apiKey + "&location=116.481488,39.990464&poitype=商务写字楼&radius=1000&extensions=all&batch=false&roadlevel=0";
    client.begin(url);
    int statusCode = client.GET();
    if (statusCode == 200)
    {
        String response = client.getString();
        Serial.println(response);
        // 在这里解析响应并提取位置信息
        // 进行相应的处理
    }
    else
    {
        Serial.println("Error getting location data. Status code: " + String(statusCode));
    }

    client.end();

    delay(10000);
}

void loopWifi()
{
    getAmapLocation();
}

void setupWifi()
{
    initWifi();
}
