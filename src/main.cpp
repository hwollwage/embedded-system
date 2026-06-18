#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <LittleFS.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

IPAddress local_IP(10,168,125,65);
IPAddress gateway(10,168,125,63);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(1,1,1,1);

const char* ssid = "iot_test";
const char* pass = "abc12345";

const uint16_t SCREEN_WIDTH = 128;
const uint16_t SCREEN_HEIGHT = 64;

Adafruit_MPU6050 mpu;
WebServer server(80);
WebSocketsServer webSocket(81);
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

constexpr uint8_t led1 = 25;
constexpr uint8_t led2 = 26;
constexpr uint8_t buzzer = 27;

float rollFiltered = 0;
float pitchFiltered = 0;

void setup() {
  Serial.begin(115200);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("oled 128x64 not found");
    for(;;);
  }

  if(!LittleFS.begin(true)) {
    Serial.println("littlefs mount failed");
    return;
  }

  WiFi.begin(ssid, pass);
  if(!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("static ip failed");
  }

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("your local ip : ");
  Serial.println(WiFi.localIP());
  
  webSocket.begin();
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if (!mpu.begin()) {
      Serial.println("MPU6050 not found");
      while (true);
  }

  Serial.println("MPU6050 Ready");
  
  server.on("/", []() {
    File file = LittleFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  });

  server.on("/ijazah-jokowi.jpg", []() {
    File file = LittleFS.open("/ijazah-jokowi.jpg", "r");
    server.streamFile(file, "image/jpeg");
    file.close();
  });

  server.on("/canvas", HTTP_GET, []() {
    File file = LittleFS.open("/canvas.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  });

  server.on("/draw", HTTP_GET , []() {
    int x1 = server.arg("x1").toInt();
    int y1 = server.arg("y1").toInt();
    int x2 = server.arg("x2").toInt();
    int y2 = server.arg("y2").toInt();

    oled.drawLine(
      x1, y1,
      x2, y2, 
      SSD1306_WHITE 
    );
    oled.display();
    server.send(200, "text/plain", "OK");
  });

  server.on("/clear", HTTP_GET, []() {
    oled.clearDisplay();
    oled.display();

    server.send(200, "text/plain", "cleared");
  });

  server.on("/test", []() {
    server.send(200, "text/plain", "ESP32 WEB OK");
  });
  
  server.begin();
}

void loop() {
  server.handleClient();
  webSocket.loop();
  sensors_event_t accel, gyro, temp;

  mpu.getEvent(&accel, &gyro, &temp);
  
  // roll = arctan(y/z)
  float roll =
    atan2(
      accel.acceleration.y, 
      accel.acceleration.z) 
      * 180.0 / PI;
  // pitch = arctan(-x / sqrt(y^2+z^2))
  float pitch =
    atan2(
      -accel.acceleration.x,
      sqrt(accel.acceleration.y * accel.acceleration.y +accel.acceleration.z * accel.acceleration.z)) 
      * 180.0 / PI;

  // Simple smoothing
  rollFiltered  = rollFiltered  * 0.9 + roll  * 0.1;
  pitchFiltered = pitchFiltered * 0.9 + pitch * 0.1;

  bool rollActive  = abs(rollFiltered) >= 50;
  bool pitchActive = abs(pitchFiltered) >= 50;

  digitalWrite(led1, rollActive);
  digitalWrite(led2, pitchActive);

  digitalWrite(buzzer, (rollActive || pitchActive));

  Serial.printf("%.2f,%.2f,%.2f,%.2f,%.2f\n",
    rollFiltered,
    pitchFiltered,
    accel.acceleration.x,
    accel.acceleration.y,
    accel.acceleration.z
  );

  static unsigned long lastSend = 0;
  if(millis() - lastSend > 20) {
    String json =
    "{"
    "\"roll\":" + String(rollFiltered,2) + ","
    "\"pitch\":" + String(pitchFiltered,2) + ","
    "\"x\":" + String(accel.acceleration.x,2) + ","
    "\"y\":" + String(accel.acceleration.y,2) + ","
    "\"z\":" + String(accel.acceleration.z,2) +
    "}";

    webSocket.broadcastTXT(json);
    lastSend = millis();
  }
  delay(20);
}