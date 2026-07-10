#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wollwage";
const char* password = "ikanhias";

constexpr uint8_t LED_PIN = 2;

WebServer server(80);

void handleRoot() {
    server.send(200, "text/plain", "ESP32 Running");
}

void handleOn() {
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/plain", "LED ON");
}

void handleOff() {
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/plain", "LED OFF");
}

void setup() {

    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/on", handleOn);
    server.on("/off", handleOff);

    server.begin();
}

void loop() {
    server.handleClient();
}