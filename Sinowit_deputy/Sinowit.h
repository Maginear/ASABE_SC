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
/*                    ������PID���� �� ���������Ĳ���                     */
/************************************************************************/
#define Stepinterval 0			// �������ÿ������֮���ʱ�� 5ms
#define ReadSensorInterval 100  // ���⴫�����Ķ�ȡ���ʱ��
#define TurnInterval 2800		// ת������Ҫ��ʱ��
#define AfterTurnInterval 200	// ת����ʱ���޵���ǰ����ʱ��

// TODO������ʵ���������ϵ��
#define PC_SENSOR 2		// �����Ŵ�ϵ��
#define IC_SENSOR 1		// ���ַŴ�ϵ��
#define DC_SENSOR 2		// ΢�ַŴ�ϵ��

#define PC_MOTOR 400	// �����Ŵ�ϵ��
#define IC_MOTOR 0		// ���ַŴ�ϵ��
#define DC_MOTOR 400	// ΢�ַŴ�ϵ��

#define Basic_Left  50 //�岽 ���ڻ�鵽10��
#define Basic_Right 50 //
#define MAX 100
#define MIN 0

typedef struct p
{
	float error_1;	// �ϴε����
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

#define MOTOR_LEFT_PIN1 31	// �� 4   
#define MOTOR_LEFT_PIN2 32	// �� 
#define MOTOR_LEFT_PIN3 33	// �� 
#define MOTOR_LEFT_PIN4 34 	// �� 

#define MOTOR_RIGHT_PIN1 36	// �� 1
#define MOTOR_RIGHT_PIN2 37	// 2
#define MOTOR_RIGHT_PIN3 38 // 3
#define MOTOR_RIGHT_PIN4 39 // 4
void TurnLeft(void);
void TurnRight(void);

/************************************************************************/
/*                 �����Ǵ������Ĳ���                                    */
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

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //��������Ȩֵ
int SENSOR[] = { SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8 };
float ReadSensor();
int numG = 0;
int numO = 0;
String readin;
/************************************************************************/
/*                            ת��Ĳ���                                 */
/************************************************************************/
//void(*afterTurnFunction)();
void(*afterForwardFunction)();

void(*afterFaceTheLineFunc)();

/************************************************************************/
/*                             ·���滮                                 */
/************************************************************************/
void rountine(void);
void backToLine(void);
void haveABreak(void);

/************************************************************************/
/*                          ����Ĳ���                                   */
/************************************************************************/
Servo servo_1, servo_2;
#endif

