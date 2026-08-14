#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

const char* ssid = "iot_test";
const char* pass = "KURWA123";

WiFiClient client;

void postHttp() {
    JsonDocument doc;
    HTTPClient http;
    String url = "http://192.168.71.139:3000/register";
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    doc["username"] = "hanzel";
    doc["password"] = "secret123";

    String body;
    serializeJson(doc, body);
    int httpCode = http.POST(body);
    if(httpCode > 0) {
        Serial.println(httpCode);
        Serial.println(http.getString());
    }else {
        Serial.println(http.errorToString(httpCode).c_str());
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.print("your ip : ");
    Serial.println(WiFi.localIP());
    postHttp();   
}

void loop() {

}