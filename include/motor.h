// #pragma once
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

void motorInit();

void forward(uint8_t speed);
void backward(uint8_t speed);
void stopMotor();

#endif