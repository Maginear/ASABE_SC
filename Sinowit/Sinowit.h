// Sinowit.h

#ifndef _SINOWIT_h
#define _SINOWIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define uchar unsigned char
#define uint unsigned int

uchar detection, sample = 0, corner = 0, k, flag;	//TODO: 暂时用不到

/************************************************************************/
/*                    以下是PID控制 和 驱动电机的参数                     */
/************************************************************************/
#define Stepinterval 4000    //步进电机每个节拍之间的时间 4ms
#define ReadSensorInterval 10000  //红外传感器的读取间隔时间

// TODO：根据实际情况调整系数
#define PC 2  // 比例放大系数
#define IC 2    //积分放大系数
#define DC 6    //大系数

#define Basic_Left  50 //五步 后期会归到10步
#define Basic_Right 50 //
#define MAX 100
#define MIN 0

/************************************************************************/
/*					以下是步进电机的参数                                 */
/************************************************************************/
// change this to the number of steps on your motor
#define STEPS 400 //因为是8拍， 所以360 / 0.9

#define motor_left_pin1 28
#define motor_left_pin2 26
#define motor_left_pin3 24
#define motor_left_pin4 22

#define motor_right_pin1 36
#define motor_right_pin2 34
#define motor_right_pin3 32
#define motor_right_pin4 30


/************************************************************************/
/*                 以下是传感器的参数                                    */
/************************************************************************/
#define sensor_num 8

#define sensor_1 46
#define sensor_2 48
#define sensor_3 50
#define sensor_4 52
#define sensor_5 47
#define sensor_6 49
#define sensor_7 51
#define sensor_8 53

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //传感器的权值
int sensor[] = { sensor_1, sensor_2, sensor_3, sensor_4, sensor_5, sensor_6, sensor_7, sensor_8 };

#endif

