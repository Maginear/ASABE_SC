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
#define ReadSensorInterval 200  //红外传感器的读取间隔时间

// TODO：根据实际情况调整系数
#define PC_sensor 2  // 比例放大系数
#define IC_sensor 2    //积分放大系数
#define DC_sensor 6    //大系数

#define PC_motor 1  // 比例放大系数
#define IC_motor 2    //积分放大系数
#define DC_motor 6    //大系数

#define Basic_Left  50 //五步 后期会归到10步
#define Basic_Right 50 //
#define MAX 100
#define MIN 0

typedef struct p
{
	float  error_1;	// 上次的误差
	float sumerror;	// 累积误差
	int pc, ic, dc;
} PID;

void PID_inti();
void updatePID();
void MotorAdjust(int);
int PIDCal(PID* pid, float error);

/************************************************************************/
/*					以下是步进电机的参数                                 */
/************************************************************************/
// change this to the number of steps on your motor
// 左轮	黑 OUT4
//      绿 OUT3
//		蓝 OUT1
//		红 OUT2

// 右轮 黑 OUT2
//		绿 OUT1
//		蓝 OUT3
//		红 OUT4
#define STEPS 400 //因为是8拍， 所以360 / 0.9

#define motor_left_pin1 22	// 左 4  
#define motor_left_pin2 24	// 左 3
#define motor_left_pin3 26	// 左 2
#define motor_left_pin4 28	// 左 1

#define motor_right_pin1 23	// 右 1
#define motor_right_pin2 25	// 3
#define motor_right_pin3 27 // 2
#define motor_right_pin4 29 // 1


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
float ReadSensor();
#endif

