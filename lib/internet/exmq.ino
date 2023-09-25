#include <wifi.ino>
#include <PubSubClient.h>



// MQTT服务器设置
const char* mqttServer = "192.168.1.89";
const int mqttPort = 1883;
const char* mqttUsername = "esp32-s3";
const char* mqttPassword = "esp32-s3";
const char* mqttClientId = "esp32-s3";

// WiFi客户端和MQTT客户端
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Received message: ");
    Serial.write(payload, length);
    Serial.println();

    // 在此处添加你对接收到的消息的处理逻辑
}

void setupExMq()
{
    initWifi();
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(callback);

    if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword))
    {
        Serial.println("Connected to MQTT server");
        mqttClient.subscribe("topic/test");
        // 在此处订阅你感兴趣的主题
        // 上报数据
        mqttClient.publish("topic/test", "init success!");
    }
    else
    {
        Serial.println("Failed to connect to MQTT server");
    }
}

// 主动上报消息
void publishData()
{
    mqttClient.publish("topic/gps", "hello world!");
}

void loopExMq()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        return;
    }
    if (!mqttClient.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword))
        {
            mqttClient.subscribe("topic/test");
        }
        else
        {
            Serial.print("Failed to connect to MQTT, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" retrying in 5 seconds...");
            delay(5000);
        }
        publishData();
    }
    mqttClient.loop();
}

