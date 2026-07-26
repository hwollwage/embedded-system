#include <Arduino.h>

constexpr uint8_t ledpin = 25;

void setup() {
    delay(4000);
    Serial.begin(115200);
    delay(4000);
    pinMode(ledpin, OUTPUT);
}

void loop() {
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    delay(1000);
}