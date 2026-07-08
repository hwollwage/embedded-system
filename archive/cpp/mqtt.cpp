#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* mqtt_server = "broker.hivemq.com";

constexpr uint8_t led1 = 25;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWifi() {
    WiFi.begin(ssid, pass);
    Serial.printf("connecting to: %s\n", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.printf(".");
        delay(500);
    }
    Serial.printf("your local ip: %s\n", WiFi.localIP().toString().c_str());
}

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for(int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }

    // kodingan orang jago katanya bram (lebih sulit lebih keren katanya)
    //
    // if(String(topic) == "esp32/output") {
    //     digitalWrite(led1, msg == "on" ? HIGH : LOW);
    // }

    Serial.printf("topic : %s\n", topic);
    Serial.printf("msg : %d\n", msg.c_str());

    if(String(topic) == "esp32/output") {
        if(msg ==  "on" || msg == "ON") {
            digitalWrite(led1, HIGH);
        }else if(msg == "off" || msg == "OFF") {
            digitalWrite(led1, LOW);
        }
    }
}

void reconnect() {
    while(!client.connected()) {
        Serial.printf("connecting to MQTT...\n");
        String clientId = "ESP32-";
        clientId += String((uint32_t)ESP.getEfuseMac(), HEX);
        // e.g. output : ESP32-abcde

        if(client.connect(clientId.c_str())) {
            Serial.printf("connected\n");
            client.subscribe("esp32/output");
        }else {
            Serial.printf("failed to connect\n");
            Serial.println("retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(led1, OUTPUT);
    pinMode(led1, LOW);
    setupWifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if(!client.connected()) reconnect();
    client.loop();

    // Publish message every 5 seconds
    // static long lastMsg = 0;
    // if (millis() - lastMsg > 5000) {
    //     lastMsg = millis();
    //     client.publish("esp32/test", "Hello from ESP32");
    // }
}