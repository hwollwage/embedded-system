#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

constexpr uint8_t gasPin = 34;
constexpr uint8_t gasPinDigital = 25;
constexpr uint8_t led = 33;
constexpr uint8_t buzzer = 26;
constexpr char DEVICE_ID[] = "ESP32-001";

const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* apiUrl = "http://192.168.0.101:8000/api/gas";


void setup() {
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);
    WiFi.begin(ssid, pass);
    Serial.printf("connecting to : %s", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("your ip : %s\n", WiFi.localIP().toString().c_str());
    
    
}

void loop() {
    JsonDocument doc;

    int gasValue = analogRead(gasPin);
    int gasAlarm = digitalRead(gasPinDigital);
    
    Serial.print("gas value : ");
    Serial.println(gasValue);
    
    if(gasAlarm == HIGH) {
        Serial.print(" | GAS DETECTED");
        digitalWrite(buzzer, HIGH);
    }else {
        digitalWrite(buzzer, LOW);
    }

    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        
        http.begin(apiUrl);
        http.addHeader("Content-Type", "application/json");

        // String json = "{\"gas\":" + String(gasValue) + "}";
        // int httpCode = http.POST(json);

        doc["device_id"] = DEVICE_ID;
        doc["gas"] = gasValue;
        doc["alarm"] = (gasAlarm == HIGH);

        String json;
        serializeJson(doc, json);

        int httpCode = http.POST(json);
        Serial.print("http code : ");
        Serial.println(httpCode);

        if(httpCode > 0) {
            Serial.println(http.getString());
        }

        http.end();
    }
    delay(5000);
}