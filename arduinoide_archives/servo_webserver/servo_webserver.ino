#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

WebServer server(80);

Servo myservo;

constexpr uint8_t SERVO_PIN = 18;

void handleRoot() {
  server.send(200, "text/html",
    R"rawliteral(
      <!DOCTYPE html>
      <html>
      <body>
        <h1>Servo Control</h1>

        <input type="range"
               min="0"
               max="180"
               value="90"
               oninput="updateServo(this.value)">

        <span id="angle">90</span>

        <script>
        function updateServo(val) {
          document.getElementById('angle').innerHTML = val;
          fetch('/servo?angle=' + val);
        }
        </script>

      </body>
      </html>
    )rawliteral"
  );
}

void handleServo() {
  if (server.hasArg("angle")) {

    int angle = server.arg("angle").toInt();

    angle = constrain(angle, 0, 180);

    myservo.write(angle);

    Serial.printf("Servo -> %d\n", angle);
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  myservo.attach(SERVO_PIN);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/servo", handleServo);

  server.begin();
}

void loop() {
  server.handleClient();
}