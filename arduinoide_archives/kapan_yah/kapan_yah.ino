#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int led = 13;
int led2 = 9;
int led3 = 8;
int button = 12;
int button2 = 10;
int buzzer = 11;

// HC-SR04
int trigPin = 6;
int echoPin = 7;

long duration;
int distance;

int buttonState = 0;
int buttonState2 = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  // HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.setCursor(0,0);
  lcd.print("System Start");
  delay(1000);
  lcd.clear();
}

void loop() {
  buttonState = digitalRead(button);
  buttonState2 = digitalRead(button2);

  // Clear trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH, 30000);

  // Convert to cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Reset output
  digitalWrite(led, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  noTone(buzzer);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0,1);

  if(buttonState == LOW && buttonState2 == LOW) {
    digitalWrite(led, HIGH);
    lcd.print("both pressed");
    tone(buzzer, 1000, 100);

  } else if(buttonState == LOW) {
    digitalWrite(led2, HIGH);
    lcd.print("button_1 ON");
    tone(buzzer, 1000, 100);

  } else if(buttonState2 == LOW) {
    digitalWrite(led3, HIGH);
    lcd.print("button_2 ON");
    tone(buzzer, 1000, 100);

  } else if(distance <= 20 && distance > 0) {
    digitalWrite(led, HIGH);
    lcd.print("TOO CLOSE");
    tone(buzzer, 1000, 100);

    // Faster beep when closer
    delay(distance * 5);

  } else if(distance <= 50) {
    digitalWrite(led2, HIGH);
    lcd.print("Moderate");
    tone(buzzer, 2000, 100);

    // Faster beep when closer
    delay(distance * 5);
  }

  else {
    lcd.print("TOO FAR");
    digitalWrite(led3, HIGH);
    delay(distance*5);
  }

  delay(100);
}