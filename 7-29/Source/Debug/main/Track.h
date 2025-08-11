/*
文件名: Track.h
描述: TB6612电机驱动
*/

#ifndef __TRACK_H
#define __TRACK_H

#include <Arduino.h>

#define TRACK_PIN_0 A0
#define TRACK_PIN_1 A1
#define TRACK_PIN_2 A2
#define TRACK_PIN_3 A3
#define TRACK_PIN_4 A4
#define TRACK_PIN_5 A5
#define TRACK_PIN_6 A6


extern int black;   //寻到黑线状态    0：未全黑   1：全黑

void Track_Init();
int Get_Track_State();

#endif
