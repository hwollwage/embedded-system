#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledPin = 13;
const int button1 = 12;
const int button2 = 11;
const int buzzer = 10;

const int trigPin = 6;
const int echoPin = 7;

long duration;
int distance;

void setup() {

  pinMode(ledPin, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("System-Start");

  delay(1000);

  lcd.clear();
}

void loop() {

  // ===== HC-SR04 =====

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  distance = duration * 0.034 / 2;

  // ===== SERIAL =====

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ===== LCD =====

  lcd.clear();

  lcd.setCursor(0,0);

  if(distance >= 100) {
    lcd.print("too far");
    digitalWrite(buzzer, LOW);
  } else {
    lcd.print("too close");
    digitalWrite(buzzer, HIGH);
  }

  // ===== BUTTONS =====

  // lcd.setCursor(0,1);

  // if(digitalRead(button1) == LOW &&
  //    digitalRead(button2) == LOW) {

  //   lcd.print("button push");

  //   digitalWrite(ledPin, HIGH);

  //   tone(buzzer, 1000);

  // } else {

  //   lcd.print("idle");

  //   digitalWrite(ledPin, LOW);

  //   noTone(buzzer);
  // }

  delay(300);
}