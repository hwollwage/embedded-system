#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int button = 10;
const int button2 = 9;
const int buzzer = 8;
const int echo = 7;
const int trig = 6;

long duration;
int distance;
bool buzzerEnabled = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("system start");
  delay(1000);
  lcd.clear();
}

void loop() {

  if(digitalRead(button) == LOW) {
    buzzerEnabled = true;
  }
  if(digitalRead(button2) == LOW) {
    buzzerEnabled = false;
  }

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 30000);

  distance = duration * 0.0343 / 2;

  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // noTone(buzzer);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);

  if(!buzzerEnabled) {
    lcd.print("buzzer off");
    delay(100);
    return;
  }

  if(distance >= 150 && distance <= 300) {
    digitalWrite(led1, HIGH);
    if(buzzerEnabled) {
      tone(buzzer, 600, 100);
    }
    lcd.print("too far");

  }else if(distance < 150 && distance >= 20) {
    digitalWrite(led2, HIGH);
    if(buzzerEnabled) {
      tone(buzzer, 1700, 100);
    }
    lcd.print("moderate");
    delay(100);

  }else {
    digitalWrite(led3, HIGH);
    if(buzzerEnabled) {
      tone(buzzer, 2000, 50);
    }
    lcd.print("too close");
    delay(300);
  }

  delay(100);
}
