#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    if(!mpu.begin()) {
        Serial.println("mpu not found");
        while(true);
    }
    Serial.println("mpu ready...");
}

void loop() {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    Serial.println();
    Serial.print("Accel X : ");
    Serial.print(accel.acceleration.x);

    Serial.print(" | Y : ");
    Serial.print(accel.acceleration.y);

    Serial.print(" | Z : ");
    Serial.print(accel.acceleration.z);
    delay(50);
}