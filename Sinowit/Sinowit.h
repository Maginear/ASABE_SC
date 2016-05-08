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

uchar detection, sample = 0, corner = 0, k, flag;	//TODO: ��ʱ�ò���

/************************************************************************/
/*                    ������PID���� �� ��������Ĳ���                     */
/************************************************************************/
#define Stepinterval 5    //�������ÿ������֮���ʱ�� 5ms
#define ReadSensorInterval 200  //���⴫�����Ķ�ȡ���ʱ��
#define TurnInterval 2000
#define AfterTurnInterval 2000

// TODO������ʵ���������ϵ��
#define PC_SENSOR 4		// �����Ŵ�ϵ��
#define IC_SENSOR 1		// ���ַŴ�ϵ��
#define DC_SENSOR 3		// ΢�ַŴ�ϵ��

#define PC_MOTOR 400	// �����Ŵ�ϵ��
#define IC_MOTOR 100	// ���ַŴ�ϵ��
#define DC_MOTOR 300	// ΢�ַŴ�ϵ��

#define Basic_Left  100 //�岽 ���ڻ�鵽10��
#define Basic_Right 100 //
#define MAX 100
#define MIN 0

typedef struct p
{
	float  error_1;	// �ϴε����
	float sumerror;	// �ۻ����
	int pc, ic, dc;
} PID;

void PID_inti();
void updatePID();
void MotorAdjust(int);
int PIDCal(PID* pid, float error);

/************************************************************************/
/*					�����ǲ�������Ĳ���                                 */
/************************************************************************/
// change this to the number of steps on your motor
// ����	�� OUT4 
//      �� OUT3
//		�� OUT1
//		�� OUT2

// ���� �� OUT2
//		�� OUT1
//		�� OUT3
//		�� OUT4
#define STEPS 400 //��Ϊ��8�ģ� ����360 / 0.9

#define MOTOR_LEFT_PIN1 22	// �� 1  
#define MOTOR_LEFT_PIN2 24	// �� 2
#define MOTOR_LEFT_PIN3 26	// �� 3
#define MOTOR_LEFT_PIN4 28	// �� 4

#define MOTOR_RIGHT_PIN1 23	// �� 4
#define MOTOR_RIGHT_PIN2 25	// 3
#define MOTOR_RIGHT_PIN3 27 // 2
#define MOTOR_RIGHT_PIN4 29 // 1
void TurnLeft(void);
void TurnRight(void);

/************************************************************************/
/*                 �����Ǵ������Ĳ���                                    */
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

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //��������Ȩֵ
int SENSOR[] = { SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8 };
float ReadSensor();
#endif

