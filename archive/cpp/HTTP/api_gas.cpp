#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

constexpr uint8_t gasAnalogPin = 33;
constexpr uint8_t gasDigitalPin = 32;
constexpr uint8_t led = 25;
constexpr uint8_t buzzer = 26;
constexpr char DEVICE_ID[] = "ESP32-01";

IPAddress local_IP(192,168,0,177);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

WiFiClient client;

const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* apiUrl = "http://192.168.0.108:8000/api/gas"; // host ip laravel from host webserver

void setup() {
    Serial.begin(115200);
    pinMode(gasAnalogPin, INPUT);
    pinMode(gasDigitalPin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);

    if(!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("STA Failed to configure");
    }

    WiFi.begin(ssid, pass);
    Serial.println();
    Serial.printf("connecting to %s\n", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("Your IP : %s\n", WiFi.localIP().toString().c_str());
}

void loop() {
    JsonDocument jsonDoc;

    int gasValue = analogRead(gasAnalogPin);
    int gasAlarm = digitalRead(gasDigitalPin); // default 1 (true)

    Serial.print("Analog : ");
    Serial.print(gasValue);

    Serial.print(" | Digital : ");
    Serial.print(gasAlarm);

    if(gasAlarm == 0) {
        digitalWrite(led, HIGH);
        digitalWrite(buzzer, HIGH);
        Serial.print(" | GAS DETECTED");
    }else {
        digitalWrite(led, LOW);
        digitalWrite(buzzer, LOW);
        Serial.print(" | SAFE");
    }

    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(client, apiUrl);
        http.addHeader("Content-Type", "application/json");

        jsonDoc["device_id"] = DEVICE_ID;
        jsonDoc["gas_value"] = gasValue;
        jsonDoc["alarm"] = (gasAlarm == 0);
        jsonDoc["ip_address"] = WiFi.localIP().toString();
        jsonDoc["wifi_rssi"] = WiFi.RSSI();
        jsonDoc["uptime_ms"] = millis();
        jsonDoc["free_heap"] = ESP.getFreeHeap();

        String json;
        serializeJson(jsonDoc, json);
        // Serial.println(json);

        int httpCode = http.POST(json);
        Serial.print(" | HTTP Code : ");
        Serial.println(httpCode);

        if(httpCode <= 0) {
            Serial.print(" | Error : ");
            Serial.print(http.errorToString(httpCode));
        }
        
        http.end();
    }
    delay(4000);
}