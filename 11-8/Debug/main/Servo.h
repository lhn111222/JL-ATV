/******************************************************************************
 * 文件名: Servo.h
 * 描述: 舵机驱动头文件
 *****************************************************************************/

#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>

void Servo_Init();
void Servo1(int angle);
void Servo2(int angle);

#endif