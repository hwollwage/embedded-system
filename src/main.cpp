#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

constexpr uint8_t GAS_ANALOG_PIN = 32;
constexpr uint8_t GAS_DIGITAL_PIN = 25;

constexpr uint32_t GAS_THRESHOLD = 2500;

HTTPClient http;

void postHttp(bool alarm) {
    JsonDocument doc;
    String url = "http://192.168.0.108:3000/api/gas";
    http.begin(url);

    doc["deviceId"] = ESP.getEfuseMac();
    doc["gasValue"] = analogRead(GAS_ANALOG_PIN);
    doc["alarm"] = alarm;
    doc["ipAddress"] = WiFi.localIP().toString().c_str();
    doc["wifiRSSI"] = WiFi.RSSI();
    doc["uptime"] = millis();
    doc["freeHeap"] = ESP.getFreeHeap();

    String body;
    serializeJson(doc, body);

    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(body);
    if(httpCode > 0) {
        Serial.println(httpCode);
        Serial.println(http.getString());
    }else {
        printf("http error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("\nyour ip: %s\n", WiFi.localIP().toString().c_str());
    pinMode(GAS_ANALOG_PIN, INPUT);
    pinMode(GAS_DIGITAL_PIN, INPUT);
}

void loop() {
    int gasAnalogValue = analogRead(GAS_ANALOG_PIN);
    int gasDigitalValue = digitalRead(GAS_DIGITAL_PIN);
    bool alarm = gasAnalogValue >= GAS_THRESHOLD;

    Serial.printf("\nGas Analog: %d\n", gasAnalogValue);
    Serial.printf("Gas Digital: %d\n", gasDigitalValue);
    Serial.printf("Alarm: %s\n", alarm ? "ON" : "OFF");
    
    postHttp(alarm);

    delay(4000);
}