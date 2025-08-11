/******************************************************************************
 * 文件名: Track.cpp
 * 描述: TB6612 电机驱动相关的轨道状态检测功能实现
 *****************************************************************************/
#include "Track.h"

int black;   //寻到黑线状态

const int NUM_READINGS = 5;
int sensorReadings[NUM_READINGS][5];

/*********************************************************************
 *  函数名称：Track_Init
 *  函数功能：循迹初始化
 ********************************************************************/
void Track_Init() {
    pinMode(TRACK_PIN_0, INPUT);
    pinMode(TRACK_PIN_1, INPUT);
    pinMode(TRACK_PIN_2, INPUT);
    pinMode(TRACK_PIN_3, INPUT);
    pinMode(TRACK_PIN_4, INPUT);
}

/*********************************************************************
 *  函数名称：Get_Track_State
 *  函数功能：获取循迹模块状态
 *  输    出：范围-2 - 0：-2大幅向左 -1轻微向左  0向前 1轻微向右 2大幅向右 3停车
 ********************************************************************/
int Get_Track_State() {
    // 进行多次读取
    for (int i = 0; i < NUM_READINGS; i++) {
        sensorReadings[i][0] =!digitalRead(TRACK_PIN_0);
        sensorReadings[i][1] =!digitalRead(TRACK_PIN_1);
        sensorReadings[i][2] =!digitalRead(TRACK_PIN_2);
        sensorReadings[i][3] =!digitalRead(TRACK_PIN_3);
        sensorReadings[i][4] =!digitalRead(TRACK_PIN_4);
    }

    // 计算平均值
    int avgSensorValues[5] = {0};
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < NUM_READINGS; i++) {
            avgSensorValues[j] += sensorReadings[i][j];
        }
        avgSensorValues[j] /= NUM_READINGS;
    }

    int sensor0 = avgSensorValues[0] << 4;
    int sensor1 = avgSensorValues[1] << 3;
    int sensor2 = avgSensorValues[2] << 2;
    int sensor3 = avgSensorValues[3] << 1;

    int sensor_state = sensor0 + sensor1 + sensor2 + sensor3 + avgSensorValues[4];

    Serial.println(sensor_state, DEC);
    //25直行，29、28微微向左，30、31大幅度向左，17、19微微向右，7、15大幅度向左，当1，3，7右转，当28、24、16右转
    if (sensor_state == 30) {
        // 需要大幅度左移
        Serial.println("大幅度左移");
        return -2;
    } else if (sensor_state == 28 || sensor_state == 25) {
        // 需要稍微左移
        Serial.println("稍微左移");
        return -1;
    } else if (sensor_state == 17 || sensor_state == 29) {
        // 需要直行
        Serial.println("直行");
        return 0;
    } else if (sensor_state == 19 || sensor_state == 23) {
        // 需要稍微右移
        Serial.println("稍微右移");
        return 1;
    } else if (sensor_state == 7 || sensor_state == 15 ) {
        // 需要大幅度右移
        Serial.println("大幅度右移");
        return 2;
    } else if (sensor_state == 7 || sensor_state == 3 || sensor_state == 1) {
        // 需要直角右转
        Serial.println("直角右移");
        return 3;
    } else if (sensor_state == 28 || sensor_state == 24 || sensor_state == 16|| sensor_state == 24) {
        // 需要直角左转
        Serial.println("直角左移");
        return -3;
    } else if (sensor_state == 0 ){
        // 停;
        Serial.println("全黑");
        black = 1;
        return 4;
    }
    else {
        // 没有这个情况 停车全白
        return 5;
    }
}
