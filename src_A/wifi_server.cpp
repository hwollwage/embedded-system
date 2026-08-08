#include "wifi_server.h"

#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

#include "config.h"
#include "motor.h"

WebServer server(80);

void wifiInit()
{
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        WiFi.begin(WIFI_SSID, WIFI_PASS);
    }

    Serial.println();
    Serial.println(WiFi.localIP());
}

void webServerInit()
{
    server.on("/", []()
    {
        File file = LittleFS.open("/motor.html");

        server.streamFile(file, "text/html");

        file.close();
    });

    server.on("/forward", []()
    {
        forward(150);
        server.send(200, "text/plain", "OK");
    });

    server.on("/backward", []()
    {
        backward(150);
        server.send(200, "text/plain", "OK");
    });

    server.on("/stop", []()
    {
        stopMotor();
        server.send(200, "text/plain", "OK");
    });

    server.onNotFound([]() {
        Serial.print("404: ");
        Serial.println(server.uri());
    
        server.send(404, "text/plain", "Not Found");
    });
    server.begin();
}

void webServerLoop()
{
    server.handleClient();
}