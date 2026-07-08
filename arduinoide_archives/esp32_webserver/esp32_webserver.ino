#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SSID";
const char* password = "PASS";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
    "<h1>hello esp32</h1>"
    "<p>esp32 webserver</p>"
  );
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("connected");
  Serial.print(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.print("web server started");

}

void loop() {
  server.handleClient();
}