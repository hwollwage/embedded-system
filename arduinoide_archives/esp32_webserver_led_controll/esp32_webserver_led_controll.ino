#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SSID";
const char* password = "PASS";

const int led1 = 27;
const int led2 = 26;
const int led3 = 25;

WebServer server(80);

void rootPage() {
  String page =
  "<h1>ESP32 led control</h1>"
  "<a href='/on'><button>LED ON</button></a>"
  "<a href='/off'><button>LED OFF</button></a>"
  "<a href='/blink'><button>LED BLINK</button><a/>";

  server.send(200, "text/html", page);
}

void ledOn() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void ledOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void ledBlink() {
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  delay(500);
  digitalWrite(led2, HIGH);
  delay(500);
  digitalWrite(led2, LOW);
  delay(500);
  digitalWrite(led3, HIGH);
  delay(500);
  digitalWrite(led3, LOW);
  delay(500);
  server.sendHeader("Location", "/blink");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(WiFi.localIP());
  
  server.on("/", rootPage);
  server.on("/on", ledOn);
  server.on("/off", ledOff);
  server.on("/blink", ledBlink);
  server.begin();
}

void loop() {
  server.handleClient();
}