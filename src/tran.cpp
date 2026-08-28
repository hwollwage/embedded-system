#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const uint8_t CE_PIN = NULL;
const uint8_t CSN_PIN = NULL;
const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const byte addr[6] = "REG01";
RF24 radio(CE_PIN, CSN_PIN);
JsonDocument doc;

void postHttp() {
    HTTPClient http;
    String url = "http://localhost:3000/api/radio";
    http.begin(url);

    http.addHeader("Content-Type", "application/json");

    doc["deviceId"] = ESP.getEfuseMac();
    doc["channel"] = channel;
    doc["hits"] = hits;
    
}

void scanRadio() {
    for(int channel = 0; channel <= 125; channel++) {
        radio.setChannel(channel);
        delay(5);

        if(radio.testRPD()) {
            Serial.printf("Channel: %d : ACTIVE", channel);
        }else {
            Serial.printf("Channel: %d : NULL", channel);
        }
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    WiFi.setAutoConnect(true);
    WiFi.persistent(true);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.printf("your ip %s\n", WiFi.localIP().toString().c_str());
    if(!radio.begin()) {
        Serial.println("nrf not found");
        for(;;);
        delay(1000);
    }   
    
    radio.stopListening();
    scanRadio();
}

void loop() {

}