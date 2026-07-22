#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
bool isConnected = false;
bool oldConnected = false;
int txValue = 0;

#define SERVICE_UUID        "69696969-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "42042042-4321-4321-4321-ba0987654321"

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        isConnected = true;
    }

    void onDisconnect(BLEServer *pServer) {
        isConnected = false;
        BLEDevice::startAdvertising(); 
        Serial.println("Client disconnected. Restarted advertising...");
    }
};

void setup() {
    Serial.begin(115200);
    BLEDevice::init("ESP32-MYBLE");
    
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    
    BLEService *pService = pServer->createService(SERVICE_UUID);
    
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE | 
        BLECharacteristic::PROPERTY_NOTIFY
    );
    
    pCharacteristic->addDescriptor(new BLE2902());
    pService->start();
    
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    
    BLEDevice::startAdvertising();
    Serial.println("BLE Started. Waiting for a client connection...");
}

void loop() {
    if (isConnected) {
        txValue = random(1, 30);
        char txString[8];
        dtostrf(txValue, 1, 2, txString);
        
        pCharacteristic->setValue(txString);
        pCharacteristic->notify();
        
        Serial.println("Sent value: " + String(txString));
        delay(500); 
    }
    // option 2 if esp32 crash / freeze cause by memory timing issue
    // if (!isConnected && oldConnected) {
    //     delay(500);
    //     BLEDevice::startAdvertising(); 
    //     Serial.println("Loop: Restarted advertising...");
    //     oldConnected = isConnected;
    // }
    
    // if (isConnected && !oldConnected) {
    //     oldConnected = isConnected;
    // }
}
