#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

HTTPClient http;

const char* ssid = "Wollwage";
const char* pass = "ikanhias";
const char* api_key = "";

void getHttp() {
  JsonDocument doc;
  WiFiClientSecure client;
  client.setInsecure();

  String url = "https://reqres.in/api/users/1";
  http.begin(url);

  http.addHeader("x-api-key", api_key);
  int httpCode = http.GET();
  Serial.println("http code ; "+httpCode);

  String response = http.getString();
  DeserializationError error = deserializeJson(doc, response);
  if(error) {
    Serial.println(error.c_str());
    http.end();
    return;
  }
  String jsonData;
  Serial.println("== data ==");
  serializeJson(doc["data"], jsonData);
  Serial.println(jsonData);
  
  Serial.println("== data name ==");
  const char* first_name = doc["data"]["first_name"];
  Serial.println(first_name);

}

void setup() {
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  getHttp();
}

void loop() {

}