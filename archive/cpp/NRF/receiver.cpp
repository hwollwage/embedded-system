#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

constexpr uint8_t CE_PIN = 9;
constexpr uint8_t CSN_PIN = 10;
constexpr uint8_t LED_PIN = 2;

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "NODE1";

bool ledState = false;

// RECEIVER

void setup()
{
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    if (!radio.begin())
    {
        Serial.println("nRF24 NOT FOUND!");

        while (true)
        {
            delay(1000);
        }
    }

    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(76);

    radio.openReadingPipe(1, address);
    radio.startListening();

    Serial.println("nRF24 RECEIVER READY");
}

void loop()
{
    if (radio.available())
    {
        char msg[32] = {0};

        radio.read(msg, sizeof(msg));

        Serial.print("Received: ");
        Serial.println(msg);

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}