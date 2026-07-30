#include <Arduino.h>

// Motor A (Kiri)
const int ENA = 25;
const int IN1 = 26;
const int IN2 = 27;

// Motor B (Kanan)
const int ENB = 14;
const int IN3 = 12;
const int IN4 = 13;

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM
  ledcAttach(ENA, 1000, 8); // pin, freq, resolution
  ledcAttach(ENB, 1000, 8);
  ledcAttach(ENB, 1200, 8);
  

  // speed awal
  ledcWrite(ENA, 200);
  ledcWrite(ENB, 200);
}

void loop() {

  // maju
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  delay(2000);

  // stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(1000);

  // mundur
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(2000);

  // stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(1000);
}