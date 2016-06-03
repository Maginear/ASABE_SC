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
/*                    以下是PID控制 和 驱动步进的参数                     */
/************************************************************************/
#define Stepinterval 0			// 步进电机每个节拍之间的时间 5ms
#define ReadSensorInterval 100  // 红外传感器的读取间隔时间
#define TurnInterval 2800		// 转弯所需要的时间
#define AfterTurnInterval 200	// 转弯后短时间无调整前进的时间

// TODO：根据实际情况调整系数
#define PC_SENSOR 2		// 比例放大系数
#define IC_SENSOR 1		// 积分放大系数
#define DC_SENSOR 2		// 微分放大系数

#define PC_MOTOR 400	// 比例放大系数
#define IC_MOTOR 0		// 积分放大系数
#define DC_MOTOR 400	// 微分放大系数

#define Basic_Left  50 //五步 后期会归到10步
#define Basic_Right 50 //
#define MAX 100
#define MIN 0

typedef struct p
{
	float error_1;	// 上次的误差
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

#define MOTOR_LEFT_PIN1 31	// 左 1   
#define MOTOR_LEFT_PIN2 32	// 左 2
#define MOTOR_LEFT_PIN3 33	// 左 3
#define MOTOR_LEFT_PIN4 34 	// 左 4

#define MOTOR_RIGHT_PIN1 36	// 右 4
#define MOTOR_RIGHT_PIN2 37	// 3
#define MOTOR_RIGHT_PIN3 38 // 2
#define MOTOR_RIGHT_PIN4 39 // 1
void TurnLeft(void);
void TurnRight(void);

/************************************************************************/
/*                 以下是传感器的参数                                    */
/************************************************************************/
#define SENSOR_NUM 8

#define SENSOR_8 3
#define SENSOR_7 27 
#define SENSOR_6 26
#define SENSOR_5 25
#define SENSOR_4 24
#define SENSOR_3 23
#define SENSOR_2 22	
#define SENSOR_1 2

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //传感器的权值
int SENSOR[] = { SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8 };
float Readsensor();

/************************************************************************/
/*                            转向的参数                                 */
/************************************************************************/
//void(*afterTurnFunction)();
void(*afterForwardFunction)();

/************************************************************************/
/*                             路径规划                                 */
/************************************************************************/
void rountine(void);
void backToLine(void);
void haveABreak(void);
#endif

