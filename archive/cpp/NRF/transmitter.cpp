#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>

constexpr uint8_t CE_PIN = 27;
constexpr uint8_t CSN_PIN = 21;

RF24 radio(CE_PIN, CSN_PIN);
const byte addr[6] = "NODE1";

// TRANSMITTER

void setup() {
    Serial.begin(115200);
    if(!radio.begin()) {
        Serial.println("nrf24 not found");
        for(;;) delay(1000);
    }

    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(76); // 2476mhz
    radio.openWritingPipe(addr);
    radio.stopListening();

    Serial.println("nrf TRANSMITTER ready");
}

void loop() {
    const char msg[] = "hello nrf from esp32";
    bool success = radio.write(&msg, sizeof(msg));
    if(success) {
        Serial.println("data sended");
    }else {
        Serial.println("failed to send data");
    }

    
    delay(2000);
}