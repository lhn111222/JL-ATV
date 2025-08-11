/*
文件名: Motor.cpp
描述: TB6612电机驱动
*/
#include "Motor.h"



/*
函数名称：Motor_Init
函数功能：电机初始化
*/
void Motor_Init()
{
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  digitalWrite(STBY,HIGH);
  pinMode(WHEEL,OUTPUT);
}



/*
函数名称：Motor_Forward
函数功能：驱动向前
形    参：左轮速度, 右轮速度
备    注：速度范围 0-255
*/
void Motor_Forward(int Left_Speed, int Right_Speed)
{
  analogWrite(PWMA,Left_Speed);
  analogWrite(PWMB,Right_Speed);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  delay(10);
}



/*
函数名称：Motor_Fallback
函数功能：驱动向后
形    参：左轮速度, 右轮速度
速度范围 0-255
*/
void Motor_Fallback(int Left_Speed, int Right_Speed)
{
  analogWrite(PWMA,Left_Speed);
  analogWrite(PWMB,Right_Speed);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  delay(10);
}



/*
函数名称：Motor_Left
函数功能：驱动向左
形    参：左轮速度, 右轮速度
速度范围 0-255
*/
void Motor_Left(int Left_Speed, int Right_Speed)
{
  // 左轮反转（后退）

  analogWrite(PWMA, Left_Speed);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  // 右轮正转（前进）
  analogWrite(PWMB, Right_Speed);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  delay(10);
}



/*
函数名称：Motor_Right
函数功能：驱动向右 
形    参：左轮速度, 右轮速度
速度范围 0-255 
*/
void Motor_Right(int Left_Speed, int Right_Speed)
{
  // 左轮正转（前进）

  analogWrite(PWMA, Left_Speed);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  
  // 右轮反转（后退）
  
  analogWrite(PWMB, Right_Speed);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  delay(10);
}



/*
函数名称：Motor_Stop
函数功能：电机停止转动
*/
void Motor_Stop()
{
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
  delay(10);
}



/*
函数名称：Track
函数功能：循迹
*/
void Track() 
{
    int sensor = Get_Track_State();  // 获取当前的循迹状态，范围是 -3 到 3

   switch (sensor)
   {
    case 0:  // 直行状态
        Motor_Forward(100, 100);  // 稍微提高直行速度
        break;
    case 1:  // 轻微向右调整
        Motor_Forward(85, 50);  // 右侧减速，左侧保持速度，轻微向右调整
        break;
    case 2:  // 中幅向右转
        Motor_Right(95, 95);  // 左侧正转，右侧反转，中幅向右调整
        break;
    case 3:  // 大幅向右转
        Motor_Right(150, 150);  // 左侧快速正转，右侧快速反转，大幅向右转
        break;
    case -1:  // 轻微向左调整
        Motor_Forward(58, 93);  // 左侧减速，右侧保持速度，轻微向左调整
        break;
    case -2:  // 中幅向左转
        Motor_Left(90, 90);  // 左侧反转，右侧正转，中幅向左调整
        break;
    case -3:  // 大幅向左转
        Motor_Left(150, 150);  // 左侧快速反转，右侧快速正转，大幅向左转
        break;
    case 4:  // 停车状态
        Motor_Stop();  // 停止电机
        break;
    case 5:  // 倒车状态
        Motor_Fallback(60, 60);  // 倒车速度
        delay(500);
        break;
    default:
        Motor_Stop();  // 如果是未知状态，默认停车
        break;
  }

}

