#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WebSocketsServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

Adafruit_MPU6050 mpu;
WebServer server(80);
WebSocketsServer webSockets(81);
JsonDocument jsonDoc;

IPAddress local_IP(192,168,0,109);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Serial.printf("Connecting to : %s\n",ssid);
    if(!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("STA failed");
    }
    
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("CONNECTED!");
    
    if(!LittleFS.begin(true)) {
        Serial.println("Mount FS failed");
        return;
    }

    server.on("/", []() {
        File file = LittleFS.open("/mpu.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    });
    
    if(!mpu.begin()) {
        Serial.println("mpu not found");
        for(;;);
    }
    Serial.println("MPU6050 READY");

    webSockets.begin();
    server.begin();
}

void loop() {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    Serial.printf("Accel X : %.2f | Y : %.2f | Z : %.2f | Gyro X : %.2f | Y : %.2f | Z : %.2f\n",
        accel.acceleration.x, accel.acceleration.y, accel.acceleration.z,
        gyro.gyro.x, gyro.gyro.y, gyro.gyro.z,
        temp.temperature);
    
    jsonDoc["ax"];
    jsonDoc["ay"];
    jsonDoc["az"];
    jsonDoc["gx"];
    jsonDoc["gy"];
    jsonDoc["gz"];
    jsonDoc["temp"];

    String json;
    
    server.handleClient();
    webSockets.loop();

    serializeJson(jsonDoc, json);
    webSockets.broadcastTXT(json);
}