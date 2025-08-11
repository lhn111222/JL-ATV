#include "Track.h"
#include "Motor.h"

// 定义阈值，用于判断传感器是否检测到黑线
// const int BLACK_THRESHOLD = 500; 
int black;   // 寻到黑线状态

const int NUM_READINGS = 5;  // 进行多次读取的次数
bool sensorReadings[NUM_READINGS][7];  // 调整为7路传感器



/*
函数名称：Track_Init
函数功能：循迹初始化
*/
void Track_Init() {
    pinMode(TRACK_PIN_0, INPUT);
    pinMode(TRACK_PIN_1, INPUT);
    pinMode(TRACK_PIN_2, INPUT);
    pinMode(TRACK_PIN_3, INPUT);
    pinMode(TRACK_PIN_4, INPUT);
    pinMode(TRACK_PIN_5, INPUT);  
    pinMode(TRACK_PIN_6, INPUT);  
}



/*
函数名称：Get_Track_State
函数功能：获取循迹模块状态
输    出：范围-3 - 3：-3大幅左转 -2中幅左转 -1轻微左转 0直行 1轻微右转 2中幅右转 
3大幅右转 4停车
适用于:  7路寻迹
*/
int Get_Track_State() {
    int sensor0 = digitalRead(TRACK_PIN_0);
    int sensor1 = digitalRead(TRACK_PIN_1);
    int sensor2 = digitalRead(TRACK_PIN_2);
    int sensor3 = digitalRead(TRACK_PIN_3);
    int sensor4 = digitalRead(TRACK_PIN_4);
    int sensor5 = digitalRead(TRACK_PIN_5);
    int sensor6 = digitalRead(TRACK_PIN_6);

    // 将传感器状态合并为一个值（利用位移操作）
    sensor0 = sensor0 << 6;
    sensor1 = sensor1 << 5;
    sensor2 = sensor2 << 4;
    sensor3 = sensor3 << 3;
    sensor4 = sensor4 << 2;
    sensor5 = sensor5 << 1;

    int sensor_state = sensor0 + sensor1 + sensor2 + sensor3 + sensor4 + sensor5 + sensor6;

    // 根据合并后的传感器状态判断车辆方向
   if (sensor_state == 0b1111111) {
     
    Serial.println("全黑状态");
    Motor_Forward(30,30);
    delay(400);
    black = 1;
    return 4;  // 停车
    
}
  if ( sensor_state == 0b1111100|| sensor_state == 0b1111110) {
    //Serial.println("大幅向左转");
    return -3;  // 大幅向左转
}
  else if (sensor_state == 0b0110000 || sensor_state == 0b1111000 || sensor_state == 0b1101000|| sensor_state == 0b1110000) {
    //Serial.println("中幅向左转");
    return -2;  // 中幅向左转
} 
  else if (sensor_state == 0b0010000 || sensor_state == 0b0011000 || sensor_state == 0b0111000|| sensor_state == 0b0111100||sensor_state == 0b1000000|| sensor_state == 0b1100000) {
    //Serial.println("轻微向左转");
    return -1;  // 轻微向左转
} 
  else if (sensor_state == 0b0001100 || sensor_state == 0b0000100 || sensor_state == 0b0011100 || sensor_state == 0b0001110) {
    //Serial.println("直行");
    return 0;   // 直行
} 
  else if (sensor_state == 0b0000110 || sensor_state == 0b0000011 || sensor_state == 0b0010110 || sensor_state == 0b0011110||sensor_state == 0b0000001 ) {
    //Serial.println("轻微向右转");
    return 1;   // 轻微向右转
} 
  else if (sensor_state == 0b0000010 || sensor_state == 0b0000111 || sensor_state == 0b0001111 || sensor_state == 0b0010111 ) {
    //Serial.println("中幅向右转");
    return 2;   // 中幅向右转
} 
  else if ( sensor_state == 0b0000011 || sensor_state == 0b0001011 || sensor_state == 0b0001111|| sensor_state == 0b0111111||sensor_state == 0b0011111) {
    //Serial.println("大幅向右转");   
    return 3;   // 大幅向右转
  } 
  else if (sensor_state == 0b0000000|| sensor_state == 0b1001111|| sensor_state == 0b01111001) {
    //Serial.println("倒车");
    return 5;  // 倒车
  }
   else {
    //Serial.println("未知状态");
    return 0;  // 出现未知状态时默认停车
   }
}