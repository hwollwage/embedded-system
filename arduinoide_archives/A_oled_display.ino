#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr uint8_t potPin = 33;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.println("starting...");
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0X3C)) {
    Serial.println("OLED not found");
    while(true);
  }
  
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(10,5);
  oled.println("OLED Bar: ");
  oled.drawRect(10, 20, 100, 30, SSD1306_WHITE);
  // oled.fillRect(12, 22, 96, 26, SSD1306_WHITE);
  
  oled.display();
}
void loop() {
    int potValue = analogRead(potPin);

    int level = map(potValue, 0, 4095, 0, 5);

    oled.fillRect(13, 23, 43, 14, SSD1306_BLACK);

    for(int i = 0; i < level; i++) {
        oled.fillRect(
            13 + i * 9,
            23,
            7,
            14,
            SSD1306_WHITE
        );
    }

    oled.display();
    delay(100);
}