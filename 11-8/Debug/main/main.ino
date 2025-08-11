#include <Arduino.h>
#include "Motor.h"
#include "Track.h"
#include "Servo.h"
//黄色十字路口第一个左转倒多了
#define SERVO_INIT 200 //辅助轮初始化角度(Servo1)是后舵机 Servo2是前舵机 200是前舵机最高 50为最低

int i = 0;
void setup() 
{
  Serial.begin(9600); //调试串口初始化
  Motor_Init();       //电机初始化
  Track_Init();      //循迹初始化
  Servo_Init();       //舵机初始化
  int num =0;         //循迹次数初始化
  black = 0;          //初始化寻全黑状态位为0 
  left_state = 0;//左直角（用来定义直角不同需要直角左转条件的变量）
  right_state = 0;//右直角（用来定义直角不同需要直角右转条件的变量）


  /*开始运行*/
  delay(1000);
  /*走过减速带*/
  Motor_Forward(100, 99);
  delay(7700);


  /*循迹到第一个十字路口  —— 过减速带后*/
  while(black == 0)  {  
    Track();     
  }
  Motor_Stop();   //寻到全黑就停车
  delay(1000);
  black = 0;

  /*直行到达草地*/
  Motor_Forward(100, 100);//直行
  delay(800);

  /*以上直行防止在第一个十字路口二次巡黑*/

  i = 200;
  while(i--)  {  
    Track();     
  }
  

  /*走草地*/
  Motor_Stop();
  Servo2(SERVO_INIT - 150);//放下去 
  delay(20);
  Motor_Forward(110, 100);
  delay(1000);
  Servo2(SERVO_INIT);//抬上来
  delay(100);
  Motor_Forward(102, 100);
  delay(4100);    //已经下草地
  Motor_Stop();

  if(Get_Track_State() == 2)  //右偏严重，人工干预纠正
  {
    Motor_Right(0, 100);
    delay(150);
    Motor_Forward(50, 100);
    delay(150);
  }
  else if(Get_Track_State() == -2)  //左偏严重，人工干预纠正
  {
    Motor_Left(100, 0);
    delay(150);
    Motor_Forward(100, 25);
    delay(150);
  }
  while(Get_Track_State() == 4)   //未完全下草地，继续直行
  {
    Motor_Forward(90, 90);
    delay(500);
  }
  while(Get_Track_State()==5)   //没太有用
  {
    Motor_Forward(0, 100);
    delay(100);
    Motor_Forward(100, 70);
    delay(100);
  }
  
/*上面3个if是用来调试当车在草地上或者未完全下草地时用的*/
//(没看出来什么用)

  /*循迹到第二个十字路口  —— 过草地后*/
  while(black == 0)  {  
    Track();   
  } 
  
  black = 0;
  right = 0;
  //Servo2(SERVO_INIT);    //抬高前辅助轮

  /*直转走方型隧道*/
  Motor_Forward(100, 100);
  delay(600);
/*以上是寻迹第二个十字路口时(下草地之后的十字路口)前进 防止二次巡黑*/
  /*循迹到第三个十字路口  —— 循迹到达方形型隧道*/
  right_state = 2;//右直角
  left_state = 1;//左直角
  while(right == 0)  {  //当跳出循环(及结束寻迹遍代表车认为已经直角右转完毕)
    Track();   
  }
  Motor_Stop();   //寻到全黑就停车
  delay(1000);
  Motor_Stop();
  //Servo2(SERVO_INIT);  //抬起前舵机
  delay(400);
  white = 0;

 
  while(white == 0)  {  //寻到直角管道的全白后跳出循环
    Track();   
  } 
  
  Motor_Stop();   //寻到全白就停车
  delay(1000);

  right_state = 0;//右直角
  right = 0;

  /*通过直角隧道*/
  Motor_Forward(100, 100);
  delay(2111);
  Motor_Fallback(100, 100);
  delay(400);
  Motor_Left(0, 105);
  delay(3150);
  Motor_Forward(105, 100);
  delay(1650);
  Motor_Left(0, 105);
  delay(2900);
  Motor_Forward(103, 100);
  delay(900);

  while(Get_Track_State() == 5)
  {
    Motor_Forward(100, 100);
    delay(100);
  }

  /*循迹到第三个十字路口  —— 循迹经过直角隧道地形*/
  black = 0;

  left_state = 3;//左直角
  while(black == 0)  {  
    Track();   
  }
  delay(1000);
  Motor_Stop();   //寻到全黑就停车
  delay(2000);
  black = 0;

  Motor_Forward(100, 100);
    delay(300);
  
 



  
  /*循迹到达窄桥前*/
   i = 120;
  while(i--)  {  
    Track();     
  }
  black = 0;

  /*上窄桥*/
  Servo2(SERVO_INIT + 30);
  Motor_Forward(130, 132);
  delay(3000);
  Motor_Stop(); 
  delay(700);

  /*上高台*/
  Motor_Left(131, 131);
  delay(1400);
  Motor_Stop();
 delay(1400);
  Motor_Forward(100, 100);
  delay(50);
  Servo2(SERVO_INIT - 150);
   delay(200);
  Motor_Forward(193, 193);
  delay(300);
  Servo1(SERVO_INIT - 110);
  delay(1300);
  Motor_Stop();
  delay(2000);

  /*下高台*/
  Motor_Fallback(130, 130);
  delay(3250);
  Motor_Stop();
  delay(1000);
  Servo1(SERVO_INIT);
  Servo2(SERVO_INIT);
  Motor_Right(130, 130);
  delay(1300);
  Motor_Stop(); //回到桥上
  delay(1000);
  Motor_Forward(100, 100);
  delay(4500);
 
  /*   循迹经过窄桥*/
 
 black = 0;
  while(black == 0)  {  
    Track();   
  }
  Motor_Stop();   //寻到全黑就停车
  delay(1000);
  black = 0;
/*下桥之后写死左转*/
 Motor_Forward(150, 135);
  delay(40);
  Motor_Left(130, 100);
  delay(1280);
  Motor_Forward(120, 110);
  delay(500);
  Motor_Stop();
 

  i = 280;
  while(i--)  {  
    Track();     
  }
  black = 0;

  /*通过防滑带*/
 Servo2(SERVO_INIT - 150);
  delay(20);
  Motor_Forward(100, 100);
  delay(1000);
  Servo2(SERVO_INIT);
  delay(100);
  Motor_Forward(105, 101);
  delay(3500);
  Motor_Stop();

  /*循迹到第五个十字路口  —— 循迹经过防滑带*/
  while(black == 0)  {  
    Track();   
  }
  Motor_Stop();   //寻到全黑就停车
  delay(1000);
  black = 0;

  /*循迹到小阶梯*/
   /*走过十字路口防止二次巡黑*/
 Motor_Forward(105, 100);
  delay(400);


 
  i = 250;
  while(i--)  {  
    Track();     
  }
  black = 0;




  
  
/*小台阶*/
  Servo2(SERVO_INIT - 150);
  delay(20);
  Motor_Forward(115, 110);
  delay(500);
  Servo2(SERVO_INIT);
  delay(20);
  Servo1(SERVO_INIT - 100);
  Motor_Forward(102, 100);
  delay(1700);
  Servo1(SERVO_INIT);
  Servo2(SERVO_INIT - 150);
  delay(20);
  Motor_Forward(102, 100);
  delay(500);
  Servo2(SERVO_INIT);
  delay(20);
  Servo1(SERVO_INIT - 100);
  Motor_Forward(103, 100);
  delay(3500);
  Servo1(SERVO_INIT);
  Servo2(SERVO_INIT-150);
  delay(800);
  Servo2(SERVO_INIT);
  Motor_Fallback(115, 115);
  delay(500);

}

void loop() {
  Motor_Stop();
}
