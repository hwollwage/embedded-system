#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const char* ssid = "SSID";
const char* password = "PASS";
const int led1 = 27;
const int led2 = 26;
const int led3 = 25;
bool ledStatus = false;

void rootPage() {
    String page =
    "<h1>webserver</h1>"
    "<a href='/on'><button>LED ON</button></a>"
    "<a href='/off'><button>LED OFF</button></a>";
    
    server.send(200, "text/html", page);
}

void ledOff() {
    ledStatus = false;
    Serial.println("LED OFF");
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    server.sendHeader("Location", "/");
    server.send(303);    
}

void ledOn() {
    ledStatus = true;
    Serial.println("LED ON");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
}

void networkAPI() {
    String json = "{";

    json += "\"ip\":\"";
    json += WiFi.localIP().toString();
    json += "\",";

    json += "\"gateway\":\"";
    json += WiFi.gatewayIP().toString();
    json += "\",";

    json += "\"status\":";
    json += String(WiFi.status());

    json += "\"mac\":";
    json += String(WiFi.macAddress());

    json += "}";

    server.send(200, "application/json", json);
}

void ledAPI() {
  String json = "{";
  json += "\"led status\":\"";
  json += (ledStatus ? "ON" : "OFF");
  json += "\"}";

  server.send(200, "application/json", json);
}

void setup() {
    Serial.begin(115200);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.print("your esp's local ip: ");
    Serial.println(WiFi.localIP());
    server.on("/", rootPage);
    server.on("/on", ledOn);
    server.on("/off", ledOff);
    server.on("/networkapi", networkAPI);
    server.on("/ledapi", ledAPI);
    server.begin();
}

void loop() {
  server.handleClient();
}