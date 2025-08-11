/*
文件名: Servo.cpp
描述: 舵机驱动
*/

#include "Servo.h"

Servo servo1;
Servo servo2;

int startAngle = 0;    // 舵机初始角度
int increment = 1;     // 舵机变量递增量
int currentAngle;      // 舵机当前角度参数



/*
函数名称：Servo_Init
函数功能：舵机初始化
*/
void Servo_Init() {
    servo1.attach(3);  // 将前舵机连接到数字引脚 3
    servo2.attach(5);  // 将后舵机连接到数字引脚 5
    currentAngle = startAngle;
}



/*
函数名称：moveServo
函数功能：舵机转动
形    参：舵机变量，转动目标角度
*/
void moveServo(Servo &servo, int targetAngle) {
    while (true) {
        servo.write(currentAngle);
        if (targetAngle > currentAngle)
            currentAngle += increment;
        else
            currentAngle -= increment;
        if (currentAngle == targetAngle) {
            currentAngle = targetAngle;
            break;
        }
        delay(15); // 调整这个延迟可以控制转动速度
    }
}

/*
函数名称：Servo1
函数功能：舵机1转动
形    参：转动角度
*/
void Servo1(int angle) {
    moveServo(servo1, angle);
}




/*
函数名称：Servo2
函数功能：舵机2转动
形    参：转动角度
*/
void Servo2(int angle) {
    moveServo(servo2, angle);
}




/*
函数名称：wheel_state
函数功能：辅助轮转动控制
形    参：状态 0：停止  1：转动
*/
void wheel_state(int state){
  if(state){
    digitalWrite(WHEEL,HIGH);
  }else{
    digitalWrite(WHEEL,LOW);
  }
}
