#include <Arduino.h>
#include <Wire.h>
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr uint8_t SERVO_PIN = 18;
constexpr uint8_t BUZZER_PIN = 25;
constexpr uint16_t SCREEN_WIDTH = 128;
constexpr uint16_t SCREEN_HEIGHT = 64;

Servo servo;
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char buffer[64];
uint8_t bufferIndex = 0;

void readSerial();
void processCommand(String cmd);
void moveServo(uint8_t angle);
void oledMessage(String title, String message);

void oledMessage(String title, String message) {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0,0);
    oled.println(title);
    oled.drawLine(0, 10, 127, 10, SSD1306_WHITE);
    oled.setCursor(0, 20);
    oled.println(message);
    oled.display();
}

void moveServo(uint8_t angle) {
    angle = constrain(angle, 0, 180);
    servo.write(angle);
    oledMessage("SERVO", "Angle: " + String(angle));
    // Serial.printf("Servo Angle : %d\n", angle);
    digitalWrite(BUZZER_PIN, angle >= 100);
}

void processCommand(String cmd) {
    Serial.print("RX: ");
    Serial.println(cmd);

    if (cmd.startsWith("ANGLE:")) {
        int angle = cmd.substring(6).toInt();
        moveServo(angle);
    } else if (cmd == "LEFT") {
        oledMessage("MOUSE", "LEFT CLICK");
    } else if (cmd == "RIGHT") {
        oledMessage("MOUSE", "RIGHT CLICK");
    } else {
        oledMessage("ERROR", "Unknown Command");
    }
}

void readSerial() {
    while (Serial.available()) {
        char c = Serial.read();

        if (c == '\n') {
            buffer[bufferIndex] = '\0';
            String command = String(buffer);
            processCommand(command);
            bufferIndex = 0;
        } else {
            if (bufferIndex < sizeof(buffer) - 1) {
                buffer[bufferIndex++] = c;
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED not found");
        while (true);
    }

    pinMode(BUZZER_PIN, OUTPUT);
    servo.attach(SERVO_PIN);
    moveServo(0);
    oledMessage("SYSTEM", "Ready");
    Serial.println("ESP32 Ready");
}

void loop() {
    readSerial();
}