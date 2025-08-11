/******************************************************************************
 * 文件名: Motor.cpp
 * 描述: TB6612 电机驱动
 *****************************************************************************/

#include "Motor.h"

#define TIME_STATE 650//延时变量

int white;
int right;
int left;
int left_state;
int right_state;
int k;
/*********************************************************************
 *  函数名称：Motor_Init
 *  函数功能：电机初始化
 ********************************************************************/
void Motor_Init() {
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);
    pinMode(WHEEL, OUTPUT);
}

/*********************************************************************
 *  函数名称：Motor_Forward
 *  函数功能：驱动向前
 *  形    参：左轮速度, 右轮速度
 *  备    注：速度范围 0-255
 ********************************************************************/
void Motor_Forward(int leftWheelSpeed, int rightWheelSpeed) {
    analogWrite(PWMA, leftWheelSpeed);
    analogWrite(PWMB, rightWheelSpeed);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(5);
}

/*********************************************************************
 *  函数名称：Motor_Fallback
 *  函数功能：驱动向后
 *  形    参：左轮速度, 右轮速度
 *  备    注：速度范围 0-255
 ********************************************************************/
void Motor_Fallback(int leftWheelSpeed, int rightWheelSpeed) {
    analogWrite(PWMA, leftWheelSpeed);
    analogWrite(PWMB, rightWheelSpeed);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    //delay(5);
}

/*********************************************************************
 *  函数名称：Motor_Left
 *  函数功能：驱动向左
 *  形    参：左轮速度, 右轮速度
 *  备    注：速度范围 0-255
 ********************************************************************/
void Motor_Left(int leftWheelSpeed, int rightWheelSpeed) {
    analogWrite(PWMA, leftWheelSpeed);
    analogWrite(PWMB, rightWheelSpeed);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    //delay(5);
}

/*********************************************************************
 *  函数名称：Motor_Right
 *  函数功能：驱动向右
 *  形    参：左轮速度, 右轮速度
 *  备    注：速度范围 0-255
 ********************************************************************/
void Motor_Right(int leftWheelSpeed, int rightWheelSpeed) {
    analogWrite(PWMA, leftWheelSpeed);
    analogWrite(PWMB, rightWheelSpeed);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    //delay(5);
}

/*********************************************************************
 *  函数名称：Motor_Stop
 *  函数功能：电机停止转动
 ********************************************************************/
void Motor_Stop() {
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    //delay(5);
}

/*********************************************************************
 *  函数名称：Track
 *  函数功能：循迹
 ********************************************************************/
void Track() {
    int trackSensorState = 0;
    int state = 0;
    int count = 0;
    trackSensorState = Get_Track_State();
    switch (trackSensorState) {
        case 0:// 需要直行
            Motor_Forward(110, 110);
            break;
        case 1:// 需要轻微右移
            Motor_Forward(100, 80);
            break;
        case 2:// 需要大幅度右移
            Motor_Right(80, 64);
            break;
        case 3:// 需要直角右转
            Motor_Forward(95, 85);
            delay(TIME_STATE+150);
            if(right_state == 4)
              delay(150);
            state = Get_Track_State();
            if(state == 5)
            {
              Motor_Fallback(100, 80);
              //直角右转(后退部分)
              if(right_state == 1)//第三个直角右转(转完后进u形管道)
                {
                  delay(TIME_STATE-250);
                  
                } 
              else if(right_state == 3)
                delay(TIME_STATE-360);
              else if(right_state == 4)//出u形管道之后的第一个右转
                delay(TIME_STATE-350);
              else if(right_state == 2)//第一个直角右转
                delay(TIME_STATE-275);
              else if(right_state == 0)//第二个直角右转(出方形管道之后)
                delay(TIME_STATE-428);

                //直角右转(右转部分)
		          Motor_Right(85, 115);
              if(right_state == 1)  //第三个直角右转(转完后进u形管道)
                delay(1700);
              else if(right_state == 2)//第一个直角右转
                delay(1680);
              else if(right_state == 3)
                delay(1200);
              else if(right_state == 4)//出u形管道后的第一个直角右转
                delay(1600);
              else if(right_state == 0)//第二个直角右转(出方形管道之后
                delay(1500);
              Motor_Forward(103, 100);
              delay(850);
              right = 1;
            }
            else           
	          {
              Motor_Fallback(100, 80);
              delay(TIME_STATE-150);
              black = 1;
              Motor_Stop();
              break;
            }
            break;


            
        case -1:// 需要稍微左移
            Motor_Forward(80, 100);
            break;
        case -2:// 需要大幅度左移
            Motor_Left(64, 80);
            break;
        case -3:// 需要直角左转
            Motor_Forward(90, 100);
            delay(TIME_STATE+100);
            state = Get_Track_State();
            if(state == 5)
            {
              if(left_state == 0) //第三个直角左转u形管道前
              {
                Motor_Fallback(105, 85);
                delay(TIME_STATE-438);
              }
              else if(left_state == 1) //直角管道前 直角左转
              { 
                Motor_Fallback(95, 75);
                delay(TIME_STATE-400);
              }
              else if(left_state == 2)//直角左转后走石头
              {
                Motor_Fallback(70, 90);
                delay(TIME_STATE-400);
              }
              else if(left_state == 3) //第二次直角左转 在黄色十字路口前
              { 
                Motor_Fallback(100, 80);
                delay(TIME_STATE-400);
              }
               else if(left_state == 5) //第4次直角左转 出u形管道后
              { 
                Motor_Fallback(105, 85);
                delay(TIME_STATE-350);
              }
              Motor_Left(115, 85);
              delay(1490);
              Motor_Forward(105, 105);
              delay(400);
              left = 1;
            }
            else
            {
              Motor_Fallback(120, 100);
              delay(TIME_STATE-200);
              black = 1;
              Motor_Stop();
            }
            break;
        case 4:  // 全黑停车
            Motor_Stop();
            break;
        default:
            white = 1;
            Motor_Stop();
    }
}
