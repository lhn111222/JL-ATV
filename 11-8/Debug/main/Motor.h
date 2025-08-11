/******************************************************************************
 * 文件名: Motor.h
 * 描述: TB6612电机驱动
 *****************************************************************************/

#ifndef __MOTOR_H
#define __MOTOR_H

#include <Arduino.h>
#include "Track.h"

#define PWMA 11      //左轮PWM调速
#define AIN1 12      //左轮正反控制
#define AIN2 13
#define STBY 10     //TB6612控制输入
#define BIN1 7     //右轮正反控制
#define BIN2 8
#define PWMB 9     //右轮PWM调速
#define WHEEL 6     //辅助轮控制

extern int white;   //寻到白线状态    0：未全白   1：全白
extern int right;
extern int left;
extern int left_state;
extern int right_state;

void Motor_Init();
void Motor_Forward(int Left_Speed, int Right_Speed);
void Motor_Fallback(int Left_Speed, int Right_Speed);
void Motor_Left(int Left_Speed, int Right_Speed);
void Motor_Right(int Left_Speed, int Right_Speed);
void Motor_Stop();
void Track();

#endif
