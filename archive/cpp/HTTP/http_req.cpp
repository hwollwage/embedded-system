#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <LittleFS.h>

HTTPClient http;
WebServer server(80);

const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* api_key = "";

String jsonData, jsonSupport;

void getHttp() {
    JsonDocument doc;
    WiFiClientSecure client;
    client.setInsecure();

    String url = "https://reqres.in/api/users/1";
    http.begin(url);

    http.addHeader("x-api-key", api_key);
    int httpCode = http.GET();
    Serial.print("http code : ");
    Serial.println(httpCode);

    String response = http.getString();

    DeserializationError error = deserializeJson(doc, response);
    if(error) {
        Serial.print("json parse failed : ");
        Serial.println(error.c_str());
        http.end();
        return;
    }
    
    JsonObject dataObj = doc["data"];
    Serial.println("=== DATA ===");
    serializeJson(doc["data"], jsonData);
    Serial.println(jsonData);
    Serial.println();

    JsonObject supportObj = doc["support"];
    Serial.println("=== SUPPORT ===");
    serializeJson(doc["support"], jsonSupport);
    Serial.println(jsonSupport);
    Serial.println();
}

void setup() {
    delay(2000);
    Serial.begin(115200);
    delay(2000);
    if(!LittleFS.begin()) {
        Serial.println("littlefs mount failed");
        return;
    }
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("Your ip : %s\n", WiFi.localIP().toString().c_str());

    getHttp();

    server.on("/", []() {
        File file = LittleFS.open("/index.html", "r");
        if(!file) {
            server.send(404, "text/plain", "index.html not found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    server.on("/api", []() {
        server.send(200, "application/json", jsonData);
    });

    server.begin();

}

void loop() {
    server.handleClient();
}

