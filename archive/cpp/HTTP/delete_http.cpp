#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

const char* ssid = "iot_test";
const char* pass = "KURWA123";
const char* api_key = "reqres_9a62200a3c4043c5b7d8b84ee90134e2";

HTTPClient http;
JsonDocument doc;
WiFiClientSecure client;

void deleteHttp() {
  client.setInsecure();
  String url = "https://reqres.in/api/users/2";
  http.begin(client, url);
  http.addHeader("x-api-key", api_key);
  int code = http.sendRequest("DELETE");
  if(code > 0) {
    Serial.print("HTTP Code : ");
    Serial.println(code);
    String response = http.getString();
    Serial.println("Raw JSON data :");
    if(response.length() == 0) {
      Serial.println("string response empty");
    }else {
      Serial.println(response);
    }
  }else {
    Serial.printf("HTTP Error : %s\n", http.errorToString(code).c_str());
  }
  http.end();
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("Your IP : %s\n", WiFi.localIP().toString().c_str());
  deleteHttp();
}

void loop() {

}