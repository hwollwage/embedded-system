#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

HTTPClient http;

const char *ssid = "iot_test";
const char *pass = "KURWA123";
const char *api_key = "reqres_9a62200a3c4043c5b7d8b84ee90134e2";

void postHttp() {
  JsonDocument doc;
  WiFiClientSecure client;
  client.setInsecure();

  String url = "https://reqres.in/api/users/2";

  http.begin(client, url);
  doc["name"] = "Hanzell";
  doc["age"] = 69;

  String body;
  serializeJson(doc, body);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", api_key);
  
  int code = http.POST(body);
  if(code > 0) {
    Serial.println(code);
    Serial.println(http.getString());
  }else {
    Serial.printf("http error : %s\n", http.errorToString(code).c_str());
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  postHttp();
}

void loop()
{
}