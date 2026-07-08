#include <Arduino.h>
#include <ESP32Servo.h>

constexpr uint8_t xServoPin = 25;
constexpr uint8_t yServoPin = 26;
constexpr uint8_t xPin = 32;
constexpr uint8_t yPin = 33;
constexpr uint8_t buttonPin = 16;

Servo servoX;
Servo servoY;

void setup() {
    Serial.begin(115200);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    servoX.attach(xServoPin);
    servoY.attach(yServoPin);
    
    servoX.write(0);
    servoY.write(0);
}

void loop() {
    const int xVal = analogRead(xPin);
    const int yVal = analogRead(yPin);
    const int buttonState = digitalRead(buttonPin);

    const int xServoPos = map(xVal, 0, 1023, 0, 180);
    const int yServoPos = map(yVal, 0, 1023, 0, 180);

    servoX.write(xServoPos);
    servoY.write(yServoPos);
    Serial.printf("Value X : %d | Y : %d | Servo Pos X : %d | Y : %d\n", xVal, yVal, xServoPos, yServoPos);

    delay(15);
}