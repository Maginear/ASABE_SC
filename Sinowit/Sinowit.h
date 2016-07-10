
#ifndef _SINOWIT_h
#define _SINOWIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define uchar unsigned char
#define uint unsigned int
// Sinowit.h 

#include <Servo.h>

uchar detection, sample = 0, corner = 0, k, flag;	//TODO: 暂时用不到
int turn_45_times = 0;

/************************************************************************/
/*                    以下是PID控制 和 驱动步进的参数                     */
/************************************************************************/
#define Stepinterval 0			// 步进电机每个节拍之间的时间 5ms
#define ReadSensorInterval 100  // 红外传感器的读取间隔时间
#define TurnInterval 1650		// 转弯所需要的时间
#define HalfTurnInterval 850	// 转弯所需要的时间
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

#define MOTOR_LEFT_PIN1 22	// 左 1   
#define MOTOR_LEFT_PIN2 23	// 左 2
#define MOTOR_LEFT_PIN3 24	// 左 3
#define MOTOR_LEFT_PIN4 25 	// 左 4

#define MOTOR_RIGHT_PIN1 26	// 右 4
#define MOTOR_RIGHT_PIN2 27	// 3
#define MOTOR_RIGHT_PIN3 28 // 2
#define MOTOR_RIGHT_PIN4 29 // 1
void TurnLeft(void);
void TurnRight(void);

/************************************************************************/
/*                 以下是传感器的参数                                    */
/************************************************************************/
#define SENSOR_NUM 8

#define SENSOR_8 3
#define SENSOR_7 36
#define SENSOR_6 35
#define SENSOR_5 34
#define SENSOR_4 33
#define SENSOR_3 32
#define SENSOR_2 31	
#define SENSOR_1 2
#define numG_1 48
#define numG_2 49
#define numG_3 50
#define numO_1 51
#define numO_2 52
#define numO_3 53
#define promixSen 21

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //传感器的权值
int SENSOR[] = { SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8 };
float ReadSensor();

/************************************************************************/
/*                            转向的参数                                 */
/************************************************************************/
//void(*afterTurnFunction)();
void(*afterForwardFunction)();
void(*afterFaceTheLineFunc)();
/************************************************************************/
/*                             路径规划                                 */
/************************************************************************/
void rountine(void);
void backToLine(void);
void haveABreak(void);

/************************************************************************/
/*							  直流电机                                  */
/************************************************************************/
#define DCmotorPin1 42 // 定义I1接口
#define DCmotorPin2 43// 定义I2接口
#define DCmotorPwm 4	// PWM口
#define DCSPEED 50
void dcDrive();
Servo servo_1;

/************************************************************************/
/*				              蓝牙通信                                   */
/************************************************************************/

int numG = 0;
int numO = 0;
int btOrder = -1;
String readin;
void readBTData(void);
void writeBTData(String);

#endif

