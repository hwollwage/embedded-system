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

void putHttp() {
  client.setInsecure();
  constexpr char URL[] = "https://reqres.in/api/users/2";
  http.begin(client, URL);

  doc["job"] = "Engineer";

  String body;
  serializeJson(doc, body);

  http.addHeader("x-api-key", api_key);
  http.addHeader("Content-Type", "application/json");

  int code = http.PUT(body);
  if(code > 0) {
    Serial.printf("http code : %d\n", code);
    Serial.printf("raw data : %s\n", http.getString().c_str());
  }else {
    Serial.printf("http error : %s\n", http.errorToString(code).c_str());
  }

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
  putHttp();
}

void loop() {

}