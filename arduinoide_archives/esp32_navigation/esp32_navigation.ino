#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SSID";
const char* pass = "PASS";

IPAddress local_ip(192, 168, 0, 169);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const int FORWARD = 27;
const int BACKWARD = 26;
const int RIGHT = 25;
const int LEFT = 33;

WebServer server(80);

void rootPage() {
  String page =
  "<h1>esp32 navigation control </h1>"
  "<a href='/forward'><button>FORWARD</button></a><br><br>"
  "<a href='/backward'><button>BACKWARD</button></a><br><br>"
  "<a href='/left'><button>LEFT</button></a><br><br>"
  "<a href='/right'><button>RIGHT</button></a>"
  "<a href='/off'><button>OFF</button></a>";

  server.send(200, "text/html", page);
}

void moveForward() {
  allOff();
  Serial.println("FORWARD Pressed");
  digitalWrite(FORWARD, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void moveBackward() {
  allOff();
  Serial.println("BACKWARD Pressed");
  digitalWrite(BACKWARD, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void moveRight() {
  allOff();
  Serial.println("RIGHT Pressed");
  digitalWrite(RIGHT, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void moveLeft() {
  allOff();
  Serial.println("LEFT Pressed");
  digitalWrite(LEFT, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void allOff() {
  digitalWrite(FORWARD, LOW);
  digitalWrite(BACKWARD, LOW);
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
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