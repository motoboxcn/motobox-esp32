#include <WiFi.h>
#include <PubSubClient.h>

// WiFi 相关设置
const char *ssid = "xiaomi-5-505";
const char *password = "mkonjibhu";

// {"clientId":"gt1glQ2SjlH.device1|securemode=2,signmethod=hmacsha256,timestamp=1691679592328|","username":"device1&gt1glQ2SjlH","mqttHostUrl":"iot-06z00irsh30z306.mqtt.iothub.aliyuncs.com","passwd":"9591edd43cb2e26ddadf841bb62127383ecc27022f9b651bfe518fc96ae0af28","port":1883}
// MQTT 相关设置
const char *mqttServer = "iot-06z00irsh30z306.mqtt.iothub.aliyuncs.com";
const int mqttPort = 1883;
const char *mqttUsername = "device1&gt1glQ2SjlH";
const char *mqttPassword = "3db274762ce91d5df7e709128bb36f33b7c105fbb388d4b6635e9b12f644efe5";
const char *mqttClientId = "gt1glQ2SjlH.device1|securemode=2,signmethod=hmacsha256,timestamp=1691679515452|";
const char *mqttTopic = "/sys/a13FN5TplKq/mqtt_basic_demo/thing/event/+/post_reply";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupWiFi()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Received message: ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setupIot()
{
    setupWiFi();

    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);
}

void loopIot()
{
    if (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword))
        {
            Serial.println("Connected to MQTT");

            mqttClient.subscribe(mqttTopic);
        }
        else
        {
            Serial.print("Failed to connect to MQTT, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" retrying in 5 seconds...");

            delay(5000);
        }
    }
    Serial.printf("loopIot\n");

    mqttClient.loop();
}