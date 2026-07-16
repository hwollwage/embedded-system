#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* mqtt_server = "broker.hivemq.com";

constexpr uint8_t SERVO_PIN = 25;
constexpr uint8_t LED_PIN = 13;
constexpr uint8_t BUZZER_PIN = 14;

WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;

void setupWifi() {
    WiFi.begin(ssid, pass);
    Serial.printf("connecting to : %s\n", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("Your Local IP : %s\n", WiFi.localIP().toString().c_str());
}

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for(int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
    
    Serial.printf("topic : %s  |  msg : %s\n",topic, msg.c_str());

    // servo
    if(String(topic) == "esp32/servo/angle") {
        int angle = msg.toInt();
        angle = constrain(angle, 0, 180);
        servo.write(angle);
        if(angle >= 150) {
            digitalWrite(LED_PIN, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
        }else {
            digitalWrite(LED_PIN, LOW);
            digitalWrite(BUZZER_PIN, LOW);
        }
    }

    // led
    if(String(topic) == "esp32/led/state") {
        if(msg == "ON") {
            digitalWrite(LED_PIN, HIGH);
        }else if(msg == "OFF") {
            digitalWrite(LED_PIN, LOW);
        }
    }

    //buzzer
    if(String(topic) == "esp32/buzzer/state") {
        if(msg == "ON") {
            digitalWrite(BUZZER_PIN, HIGH);
        }else if(msg == "OFF") {
            digitalWrite(BUZZER_PIN, LOW);
        }
    }
    
}

void reconnect() {
    while(!client.connected()) {
        Serial.print("connecting MQTT");
        
        String clientId = "ESP32-";
        clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

        if(client.connect(clientId.c_str())) {
            Serial.println("connected");

            client.subscribe("esp32/servo/angle");
            client.subscribe("esp32/led/state");
            client.subscribe("esp32/buzzer/state");

            Serial.println("subscribed");
        }else {
            Serial.print("failed, rc=");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    servo.attach(SERVO_PIN);
    servo.write(0);
    setupWifi();

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if(!client.connected()) {
        reconnect();
    }
    client.loop();
}