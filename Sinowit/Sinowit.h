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
#define Stepinterval 5    //步进电机每个节拍之间的时间 5ms
#define ReadSensorInterval 200  //红外传感器的读取间隔时间
#define TurnInterval 1000
#define AfterTurnInterval 2000

// TODO：根据实际情况调整系数
#define PC_SENSOR 4		// 比例放大系数
#define IC_SENSOR 1		// 积分放大系数
#define DC_SENSOR 3		// 微分放大系数

#define PC_MOTOR 400	// 比例放大系数
#define IC_MOTOR 100	// 积分放大系数
#define DC_MOTOR 300	// 微分放大系数

#define Basic_Left  100 //五步 后期会归到10步
#define Basic_Right 100 //
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

#define MOTOR_LEFT_PIN1 22	// 左 4  
#define MOTOR_LEFT_PIN2 24	// 左 3
#define MOTOR_LEFT_PIN3 26	// 左 2
#define MOTOR_LEFT_PIN4 28	// 左 1

#define MOTOR_RIGHT_PIN1 23	// 右 1
#define MOTOR_RIGHT_PIN2 25	// 3
#define MOTOR_RIGHT_PIN3 27 // 2
#define MOTOR_RIGHT_PIN4 29 // 1
void TurnLeft(void);
void TurnRight(void);

/************************************************************************/
/*                 以下是传感器的参数                                    */
/************************************************************************/
#define SENSOR_NUM 8

#define SENSOR_1 46
#define SENSOR_2 48
#define SENSOR_3 50
#define SENSOR_4 52
#define SENSOR_5 47
#define SENSOR_6 49
#define SENSOR_7 51
#define SENSOR_8 53

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //传感器的权值
int SENSOR[] = { SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8 };
float ReadSensor();
#endif

