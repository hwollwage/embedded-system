#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// =========================
// NRF24
// =========================

const uint8_t CE_PIN = 4;
const uint8_t CSN_PIN = 5;

RF24 radio(CE_PIN, CSN_PIN);

// =========================
// WiFi
// =========================

const char* ssid = "Wollwage";
const char* pass = "ikanhias";

// =========================
// API
// =========================

const char* serverURL = "http://192.168.1.100:3000/api/radio";

// =========================
// Device
// =========================

const byte addr[6] = "REG01";


// =====================================================
// SCAN RADIO
// =====================================================

void scanRadio() {

    Serial.println("Starting scan...");

    for (int channel = 0; channel <= 125; channel++) {

        radio.setChannel(channel);

        int hits = 0;

        for (int i = 0; i < 100; i++) {

            if (radio.testRPD()) {
                hits++;
            }

            delay(2);
        }

        Serial.printf(
            "Channel: %3d | Hits: %d/100\n",
            channel,
            hits
        );
    }

    Serial.println("Scan complete.");
}


// =====================================================
// SETUP
// =====================================================

void setup() {

    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("ESP32 starting...");


    // =========================
    // WIFI
    // =========================

    Serial.println("Connecting WiFi...");

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {

        Serial.print(".");

        delay(500);
    }

    Serial.println();
    Serial.println("WiFi connected!");

    Serial.printf(
        "IP Address: %s\n",
        WiFi.localIP().toString().c_str()
    );


    // =========================
    // NRF24 BEGIN
    // =========================

    Serial.println("Starting NRF24...");

    if (!radio.begin()) {

        Serial.println("NRF24 NOT FOUND!");

        while (true) {
            delay(1000);
        }
    }

    Serial.println("NRF24 OK");


    // =========================
    // NRF24 CONFIG
    // =========================

    radio.setPALevel(RF24_PA_LOW);

    radio.setDataRate(RF24_1MBPS);

    radio.setCRCLength(RF24_CRC_16);

    // Masuk listening mode
    radio.startListening();


    // =========================
    // START SCAN
    // =========================

    scanRadio();
}


// =====================================================
// LOOP
// =====================================================

void loop() {

}