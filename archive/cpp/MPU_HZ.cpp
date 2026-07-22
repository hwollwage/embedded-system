#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// #include <Wire.h>
#include <Arduino.h>
#include <ESP32Servo.h>

Adafruit_MPU6050 mpu;
Servo servo;

const int SERVO_PIN = 25; 

float pitch = 0;
float servoAngle = 90;

float mapTheFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  // servoAngle = mapTheFloat(pitch, -45, 45, 0 ,180); 
}

void setup() {
  Serial.begin(115200);
  delay(3000);
  // Wire.begin();
  if(!mpu.begin()) {
    Serial.println("mpu not found");
    for(;;);
  }
  Serial.println("MPU READY");

  // up -> larger measure, down -> more precise
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // up -> faster rotation measu. down -> more precise
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // up -> more responsive (more noise), down -> slower (smoother)
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);
  servo.write(90);
  delay(1000);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  pitch = atan2(accel.acceleration.x, sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
  
  servoAngle = mapTheFloat(pitch, -45, 45, 0 ,180); 
  servoAngle = constrain(servoAngle, 0, 180);
  
  servo.write((int)servoAngle);

  Serial.printf("Pitch: %.2f deg | Servo : %.2f deg\n", pitch, servoAngle);
  delay(10);
}
