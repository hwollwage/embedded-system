#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

float rollFiltered = 0;
float pitchFiltered = 0;

void setup() {
    Serial.begin(115200);

    if (!mpu.begin()) {
        Serial.println("MPU6050 not found");
        while (true);
    }

    Serial.println("MPU6050 Ready");
}

void loop() {
    sensors_event_t accel, gyro, temp;

    mpu.getEvent(&accel, &gyro, &temp);
    // roll = arctan(y/z)
    float roll =
        atan2(accel.acceleration.y, accel.acceleration.z) * 180.0 / PI;
    // pitch = archtan(-x / sqrt(y^2+z^2))
    float pitch =
        atan2(-accel.acceleration.x,sqrt(accel.acceleration.y * accel.acceleration.y +accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
    // Simple smoothing
    rollFiltered  = rollFiltered  * 0.9 + roll  * 0.1;
    pitchFiltered = pitchFiltered * 0.9 + pitch * 0.1;

    Serial.printf("%.2f,%.2f\n",
                  rollFiltered,
                  pitchFiltered);

    delay(20);
}