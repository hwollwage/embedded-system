#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
WebServer server(80);

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

IPAddress local_ip(192, 168, 0, 169);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

constexpr int FORWARD = 27;
constexpr int BACKWARD = 26;
constexpr int RIGHT = 25;
constexpr int LEFT = 33;


void rootPage() {
  String page =
  "<h1>esp32 navigation control </h1>"
  "<a href='/forward'><button style='width: 300px; height: 150px; background-color: #ff7e73'>FORWARD</button></a><br><br>"
  "<a href='/backward'><button style='width: 300px; height: 150px; background-color: #ffe873'>BACKWARD</button></a><br><br>"
  "<a href='/left'><button style='width: 300px; height: 150px; background-color: #73ff7c'>LEFT</button></a><br><br>"
  "<a href='/right'><button style='width: 300px; height: 150px; background-color: #87bbff'>RIGHT</button></a><br><br>"
  "<a href='/off'><button style='width: 300px; height: 150px; background-color: #ff87ff'>OFF</button></a>";

  server.send(200, "text/html", page);
}

void moveForward() {
  allOff();
  Serial.println("FORWARD Pressed");
  digitalWrite(FORWARD, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FORWARD");
  server.sendHeader("Location", "/");
  server.send(303);
}

void moveBackward() {
  allOff();
  Serial.println("BACKWARD Pressed");
  digitalWrite(BACKWARD, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BACKWARD");
  server.sendHeader("Location", "/");
  server.send(303);
}

void moveRight() {
  allOff();
  Serial.println("RIGHT Pressed");
  digitalWrite(RIGHT, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RIGHT");
  server.sendHeader("Location", "/");
  server.send(303);
}

void moveLeft() {
  allOff();
  Serial.println("LEFT Pressed");
  digitalWrite(LEFT, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LEFT");
  server.sendHeader("Location", "/");
  server.send(303);
}

void allOff() {
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALL OFF");
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(FORWARD, OUTPUT);
  pinMode(BACKWARD, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);

  if(!WiFi.config(local_ip, gateway, subnet)) {
    Serial.println("failed configuring static ip");
  }

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(1000);
  }
  Serial.println();
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  server.on("/", rootPage);
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/right", moveRight);
  server.on("/left", moveLeft);
  server.on("/off", allOff);
  server.begin();
}

void loop() {
  server.handleClient();
}