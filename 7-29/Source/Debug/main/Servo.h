#ifndef __SERVO_H
#define __SERVO_H

#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"

extern int startAngle;    // 舵机初始角度
extern int increment;     // 舵机变量递增量
extern int currentAngle;      // 舵机当前角度参数

void Servo_Init();
void Servo1(int angle);
void Servo2(int angle);

void wheel_state(int state);

#endif
