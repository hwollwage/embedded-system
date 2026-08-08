#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
// a = high val -> night | low val -> day
// d = 0 (day) 1 (night)

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

IPAddress local_IP(192,168,0,169);
IPAddress subnet(255,255,255,0);
IPAddress gateway(192,168,0,1);

WiFiClient client;

constexpr uint8_t analogLightPin = 34;
constexpr uint8_t digitalLightPin = 35;

void setupWifi() {
    WiFi.setAutoConnect(true);
    WiFi.persistent(true);

    if(!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("STA Failed");
    }

    WiFi.begin(ssid, pass);
    Serial.printf("Connecting to : %s\n", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("CONNECTED!");
    Serial.printf("Your IP : %s\n", WiFi.localIP().toString().c_str());
}

void postHttp() {
    JsonDocument doc;
    HTTPClient http;
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Wifi disconnected, skipping POST");
        return;
    }
    const char* apiUrl = "http://192.168.0.108:3000/api/light";
    http.begin(client, apiUrl);

    short aVal = analogRead(analogLightPin);
    bool dVal = digitalRead(digitalLightPin);
    
    JsonObject wifi = doc["wifi"].to<JsonObject>();

    doc["analog_light"] = aVal;
    doc["digital_light"] = dVal;
    doc["uptime"] = millis();

    wifi["rssi"] = WiFi.RSSI();
    wifi["bssid"] = WiFi.BSSIDstr();

    String body;
    serializeJson(doc, body);

    http.addHeader("Content-Type", "application/json");
    
    int httpCode = http.POST(body);
    if(httpCode > 0) {
        Serial.println(httpCode);
        Serial.println(http.getString());
    }else {
        Serial.printf("error : %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}

void setup() {
    Serial.begin(115200);
    setupWifi();
    pinMode(analogLightPin, INPUT);
    pinMode(digitalLightPin, INPUT);
}

void loop() {
    postHttp();
    delay(4000);
}
