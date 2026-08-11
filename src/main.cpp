#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

constexpr uint8_t ENA = 16;
constexpr uint8_t ENB = 17;
constexpr uint8_t IN1 = 18;
constexpr uint8_t IN2 = 19;
constexpr uint8_t IN3 = 14;
constexpr uint8_t IN4 = 25;

// PID
float Kp = 0.0f;
float Ki = 0.0f;
float Kd = 0.0f;

float targetAngle = 0.0f;
float error = 0.0f;
float prevError = 0.0f;
float integral = 0.0f;
float pidOutput = 0.0f;
float angle = 0.0f;

uint32_t prevMicros = 0;

void setMotor(int leftSpeed, int rightSpeed) {
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);

    if(leftSpeed > 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }else if(rightSpeed < 0) {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }else {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
    }

    analogWrite(ENB, abs(rightSpeed));
}

void updateAngle(float dt) {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    // accel angle : arctan(a^x, a^z) * 180 / pi -> div to get degree format
    float accelAngle = atan2(accel.acceleration.x, accel.acceleration.z) * 180.0f / PI;
    // gyro rate (kecepatan sudut) : theta * (180 / pi) -> div to get degree format
    float gyroRate = gyro.gyro.y * 180.0f / PI;

    angle = 0.98f * (angle + gyroRate * dt) + 0.02f * accelAngle;
}

float calculatePID(float dt) {
    error = targetAngle - angle;
    integral += error * dt;
    integral = constrain(integral, -100.0f, 100.0f);

    float derivative = (error - prevError) / dt;
    float output = Kp * error + Ki * integral + Kd * derivative;
    
    return output;
}

void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    setMotor(0, 0);

    Wire.begin();
    if(!mpu.begin()) {
        Serial.println("mpu not found");
        for(;;);
    }
    Serial.println("mpu ok");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    prevMicros = micros();
}

void loop() {
    uint32_t now = micros();

    float dt = (now - prevMicros) / 1000000.0f; // 1_000_000
    if(dt < 0.005f) return; // 200Hz, yknow what im sayin
    prevMicros = now;

    updateAngle(dt);
    pidOutput = calculatePID(dt);

    int motorOutput = constrain((int)pidOutput, -255, 255);

    setMotor(motorOutput, motorOutput);

    Serial.printf("angle ; %f | pid ; %f\n", angle, pidOutput);
}