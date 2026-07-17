#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

Adafruit_MPU6050 mpu;
WebServer server(80);
WebSocketsServer webSocket(81);

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

void setup() {
    Serial.begin(115200);
    if(!mpu.begin()) {
        Serial.println("mpu not found");
        for(;;);
    }
    Serial.println("mpu ready");
    if(!LittleFS.begin(true)) {
        Serial.println("littlefs mount failed");
        return;
    }
    WiFi.begin(ssid, pass);
    Serial.print("connecting to : ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.println(".");
        delay(500);
    }
    Serial.println("CONNECTED!");
    Serial.printf("Your ip : %s\n", WiFi.localIP().toString().c_str());

    webSocket.begin();

    server.on("/", []() {
        File file = LittleFS.open("/mpu.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    });

    server.begin();
}

void loop() {
    JsonDocument jsonDoc;
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);
    Serial.println();
    Serial.printf(
        "Accel X: %.2f | Y: %.2f | Z: %.2f | Gyro X: %.2f | Y: %.2f | Z: %.2f | Temp: %.2f C\n",
        accel.acceleration.x,
        accel.acceleration.y,
        accel.acceleration.z,
        gyro.gyro.x,
        gyro.gyro.y,
        gyro.gyro.z,
        temp.temperature
    );

    jsonDoc["Ax"] = accel.acceleration.x;
    jsonDoc["Ay"] = accel.acceleration.y;
    jsonDoc["Az"] = accel.acceleration.z;
    jsonDoc["Gx"] = gyro.gyro.x;
    jsonDoc["Gy"] = gyro.gyro.y;
    jsonDoc["Gz"] = gyro.gyro.z;
    jsonDoc["temp"] = temp.temperature;

    String json;

    server.handleClient();
    webSocket.loop();
    serializeJson(jsonDoc, json);
    webSocket.broadcastTXT(json);
    
    delay(50);
}
