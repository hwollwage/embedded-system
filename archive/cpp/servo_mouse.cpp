#include <Arduino.h> 
#include <ESP32Servo.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

constexpr uint8_t servoPin = 18; 
constexpr uint16_t SCREEN_WIDTH = 128; 
constexpr uint16_t SCREEN_HEIGHT = 64; 
constexpr uint8_t buzzerPin = 25;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 
Servo myservo; 

void showMessageOled(String title, String message) {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println(title);
  oled.drawLine(0,10,127,10, SSD1306_WHITE);
  oled.setCursor(0,20);
  oled.println(message);
  oled.display();
}

void setup() { 
  Serial.begin(115200); 
  delay(2000); 
  
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.printf("OLED not found\n"); 
    while(true); 
  } 
  
  oled.clearDisplay(); 
  oled.setTextSize(1); 
  oled.setTextColor(WHITE);
  oled.setCursor(10, 5); 
  oled.printf("SERVO ANGLE MONITOR"); 
  oled.display(); 
  
  pinMode(buzzerPin, OUTPUT);

  myservo.attach(servoPin); 
  myservo.write(100); 
  Serial.printf("servo ready...\n"); 
} 

void loop() { 
  if(Serial.available()) { 
    String data = Serial.readStringUntil('\n'); 
    data.trim();
    
    if(data.startsWith("ANGLE:")) {
      int angle = data.substring(6).toInt(); 
      angle = constrain(angle, 0 , 180); 
      
      myservo.write(angle); 
      showMessageOled("SERVO", "Angle: "+String(angle));
      Serial.printf("servo at angle : %d\n", angle);
      
      if(angle >= 100) {
        digitalWrite(buzzerPin, HIGH);
      }else {
        digitalWrite(buzzerPin, LOW);
      }

    }else if(data.startsWith("LEFT")) {
      showMessageOled("MOUSE", "LEFT CLICK");
      Serial.printf("left mouse clicked\n");
    }else if(data.startsWith("RIGHT")) {
      showMessageOled("MOUSE", "RIGHT CLICK");
      Serial.printf("right mouse clicked\n");
    }else {
      showMessageOled("ERROR", "Unknown command");
      Serial.printf("unknown command inserted\n");
    }
  } 
}
