#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

constexpr uint8_t xServoPin = 25;
constexpr uint8_t yServoPin = 26;
constexpr uint8_t xPin = 32;
constexpr uint8_t yPin = 33;
constexpr uint8_t buttonPin = 16;

int xServoPos = 0;
int yServoPos = 0;

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

Servo servoX;
Servo servoY;
WebServer server(80);


void setup() {
    Serial.begin(115200);
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    servoX.attach(xServoPin);
    servoY.attach(yServoPin);
    
    servoX.write(0);
    servoY.write(0);

    WiFi.begin(ssid, pass);
    Serial.printf("connecting to : %s\n", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.printf("your ip : %s\n", WiFi.localIP().toString().c_str());

    if(!LittleFS.begin(true)) {
        Serial.printf("mount littleFS failed\n");
        return;
    }

    server.on("/", []() {
        File file = LittleFS.open("/joystick.html", "r");
        if(!file) {
            server.send(404, "text/plain", "joystick.html not found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    server.on("/move", []() {
        String dir = server.arg("dir");
        if(dir == "up") {
            yServoPos += 5;
        }else if(dir == "down") {
            yServoPos -= 5;
        }else if(dir == "left") {
            xServoPos -= 5;
        }else if(dir == "right") {
            xServoPos += 5;
        }else if(dir == "center") {
            xServoPos = 90;
            yServoPos = 90;
        }

        xServoPos = constrain(xServoPos, 0, 180);
        yServoPos = constrain(yServoPos, 0, 180);
    });

    server.begin();
}

void loop() {
    int xVal = analogRead(xPin);
    int yVal = analogRead(yPin);
    int buttonState = digitalRead(buttonPin);

    const int xServoPos = map(xVal, 0, 1023, 0, 180);
    const int yServoPos = map(yVal, 0, 1023, 0, 180);

    servoX.write(xServoPos);
    servoY.write(yServoPos);
    Serial.printf("Value X : %d | Y : %d | Servo Pos X : %d | Y : %d\n", xVal, yVal, xServoPos, yServoPos);

    delay(15);
}