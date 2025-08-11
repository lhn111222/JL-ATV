#include <Arduino.h>
#include "Motor.h"
#include "Track.h"
#include "Servo.h"

/*已完成部分*/

void setup() 
{
  Serial.begin(9600); //调试串口初始化
  Motor_Init();       //电机初始化
  Track_Init();      //循迹初始化
  // Servo_Init();       //舵机初始化
  //int num =0;         //循迹次数初始化
   black = 0;          //初始化寻全黑状态位为0  0为开始寻迹


  /*开始运行*/
  delay(1000);


  //走过第一个T字路口  —— 栅格前
  Motor_Forward(220, 215); 
  delay(800);


  /*栅格操作*/
Motor_Fallback(60, 60);
 Serial.println("倒车");
    delay(1000);
    Motor_Forward(220,220);
    delay(1500);
    Motor_Stop();
   Serial.println("预备");
    delay(1000);
    Motor_Forward(90, 90); 
   Serial.println("直行");
    delay(800);
    Motor_Stop();
    delay(2000);


  /*循迹到第一个十字路口*/
  /*过栅格后 U形隧道*/
  black = 0;   
  while(black == 0)  
  {  
    Track();     
  }
  delay(2000);
  Motor_Left(90,90);
  delay(400);
  Motor_Stop();   //寻到全黑就停车
  delay(400);
  black = 0;
  
  /*循迹到第二个十字路口*/
  /*过方形隧道*/
 while(black == 0)  
  {  
    Track();     
  }
  
   delay(1000);
 Motor_Left(90,90);
   delay(600);

   Motor_Stop();   //寻到全黑就停车
  delay(400);

    black = 0;
  while(black == 0)  
  {  
    Track();     
  }

 black = 0;
/***********************************************************/







/*未完成部分
*****************************************************
  // /*左转走U型隧道*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Left(200, 200); 
  // delay(550);
  // Motor_Stop();
//***************************************************

  // //循迹到第二个十字路口  —— 循迹经过U型隧道
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // /*左转走方型隧道*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Left(200, 200); 
  // delay(550);
  // Motor_Stop();

  // //循迹到第三个十字路口  —— 循迹经过方形型隧道
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // /*左转走石块地形*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Left(200, 200); 
  // delay(550);
  // Motor_Stop();

  // /*走石块地形*/

  // //循迹到第四个十字路口  —— 循迹经过石块地形
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // /*右转走小型阶梯*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Right(200, 200); 
  // delay(550);
  // Motor_Stop();

  // /*走小型阶梯*/

  // //循迹到第五个十字路口  —— 循迹经过方形型隧道
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // /*直行走防滑带*/
  // Motor_Forward(200, 200);
  // delay(200);
  // Motor_Stop();

  // //循迹到第六个十字路口  —— 循迹经过防滑带
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // /*右转走小型阶梯*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Right(200, 200); 
  // delay(550);
  // Motor_Stop();

  // /*上窄桥*/
  // num = 70;
  // while(num --)  {  
  //   Track();   
  // }
  // Motor_Stop();
  // delay(1500);

  // Motor_Forward(205, 200);
  // delay(1700);
  // Motor_Stop();

  // /*右转上平台*/
  // delay(1000);
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Right(200, 200); 
  // delay(850);
  // Motor_Stop();

  // /*到达平台中心*/
  // Motor_Forward(200, 200);
  // delay(2500);
  // Motor_Stop();

  // /*左转到大型阶梯*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Left(200, 200); 
  // delay(550);
  // Motor_Stop();

  // /*上大型阶梯*/
  // delay(1000);
  // Motor_Forward(200, 200);
  // delay(2800);
  // Motor_Stop();

  // /*右转走下型阶梯*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Right(200, 200); 
  // delay(850);
  // Motor_Stop();

  // /*下大型阶梯*/
  // Motor_Forward(200, 200);
  // delay(1500);
  // Motor_Stop();

  // //循迹到第八个十字路口  —— 循迹通过大型阶梯
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // /*右转走草地*/
  // Motor_Forward(200, 200);
  // delay(20);
  // Motor_Right(200, 200); 
  // delay(550);
  // Motor_Stop();

  // //循迹到第九个十字路口  —— 循迹通过草地
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // //直行走减速带
  // Motor_Forward(200, 200);
  // delay(400);
  // Motor_Stop();

  // //循迹到第十个十字路口  —— 循迹通过减速带
  // while(black == 0)  {  
  //   Track();   
  // }
  // delay(2000);
  // Motor_Stop();   //寻到全黑就停车
  // black = 0;

  // //直行到达终点
  // Motor_Forward(200, 200);
  // delay(2000);
  // Motor_Stop();

}

void loop() {
  //循迹到第三个十字路口  —— 循迹经过U型隧道
  while (black == 0) 
  {
    Track();
  }
  
  // delay(2000);
  //Motor_Stop();   //寻到全黑就停车
  // black = 0;
}
