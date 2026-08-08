#include <Arduino.h>
#include <LittleFS.h>

#include "motor.h"
#include "wifi_server.h"

void setup()
{
    Serial.begin(115200);

    LittleFS.begin();

    motorInit();

    wifiInit();

    webServerInit();
}

void loop()
{
    webServerLoop();
}