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
    int angle = data.toInt(); 
    angle = constrain(angle, 0 , 180); 
    
    myservo.write(angle); 
    Serial.printf("servo at angle : %d\n", angle);
    
    if(angle >= 100) {
      Serial.printf("angle is more than 100\n");
      digitalWrite(buzzerPin, HIGH);
    }else {
      digitalWrite(buzzerPin, LOW);
    }
    
    // Clear and update OLED properly
    oled.clearDisplay(); 
    oled.setCursor(10, 5); 
    oled.printf("SERVO ANGLE MONITOR");
    
    oled.setCursor(10, 20); // Moved down slightly for separation
    oled.printf("servo angle : %d", angle); 
    oled.display(); // You missed this call in loop()
  } 
}
