#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int led = 13;
const int led2 = 12;
const int led3 = 11;

const int button = 10;
const int button2 = 9;
const int button3 = 8;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("starting...");
  delay(1000);
  lcd.clear();
}

void loop() {

  bool b1 = digitalRead(button) == LOW;
  bool b2 = digitalRead(button2) == LOW;
  bool b3 = digitalRead(button3) == LOW;
  int count = b1+b2+b3;

  if (count == 3) {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("3 buttons");
  }
  else if (count == 2) {
    digitalWrite(led, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("2 buttons");
  }
  else if(count == 1) {
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1 buttons");
  }else {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("idle");
  }
  delay(200);
}