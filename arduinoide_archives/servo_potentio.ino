#include <ESP32Servo.h>

constexpr uint8_t pot = 34;
constexpr uint8_t servo = 26;

Servo myservo;

void setup() {
  Serial.begin(115200);
  myservo.attach(servo);
}

void loop() {
  int potValue = analogRead(pot);
  int angle = map(potValue, 0, 4095, 0, 180);

  myservo.write(angle);

  // spin continuously
  // for(int angle = 0; angle <= 180; angle++) {
  //   myservo.write(angle);
  //   delay(15);
  // }

  // for(int angle = 180; angle >= 0; angle--) {
  //   myservo.write(angle);
  //   delay(15);
  // }

  Serial.print("Potentiometer Val: ");
  Serial.print(potValue);
  Serial.print(" | Servo angle: ");
  Serial.println(angle);

  delay(20);
}