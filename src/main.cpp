#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

Servo servo;
WiFiClient esp32;
PubSubClient client(esp32);
JsonDocument jsonDoc;


const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* mqtt_server = "broker.hivemq.com";

// IPAddress local_IP(192,168,0,109);
// IPAddress gateway(192,168,0,1);
// IPAddress subnet(255,255,255,0);
// IPAddress primaryDNS(8,8,8,8);
// IPAddress secondaryDNS(1,1,1,1);

constexpr uint8_t SERVO_PIN = 25;

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for(int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
    Serial.printf("Topic : %s | Message : %s\n", topic, msg.c_str());

    if(String(topic) == "servo/angle") {
        int angle = msg.toInt();
        angle = constrain(angle,0,180);
        servo.write(angle);
    }
}

void reconnect() {
    if(!client.connected()) {
        Serial.println("Connecting to MQTT...");

        String clientId = "ESP32-";
        clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

        if(client.connect(clientId.c_str())) {
            Serial.println("CONNECTED TO MQTT");
            
            client.subscribe("servo/angle");
            Serial.println("SUBSCRIBED");
        }else {
            Serial.print("Failed, rc=");
            Serial.println(client.state());
            delay(4000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    // if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    //     Serial.println("STA Failed");
    // }
    WiFi.begin(ssid, pass);
    Serial.printf("Connecting to %s\n", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("CONNECTED");
    Serial.printf("Your IP : %s\n", WiFi.localIP().toString().c_str());
    
    servo.attach(SERVO_PIN);
    servo.write(0);

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if(!client.connected()) reconnect();
    client.loop();
}