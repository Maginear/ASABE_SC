
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

uchar detection, sample = 0, corner = 0, k, flag;	//TODO: ��ʱ�ò���
int turn_45_times = 0;

/************************************************************************/
/*                    ������PID���� �� ���������Ĳ���                     */
/************************************************************************/
#define Stepinterval 0			// �������ÿ������֮���ʱ�� 5ms
#define ReadSensorInterval 100  // ���⴫�����Ķ�ȡ���ʱ��
#define TurnInterval 1650		// ת������Ҫ��ʱ��
#define HalfTurnInterval 850	// ת������Ҫ��ʱ��
#define AfterTurnInterval 200	// ת����ʱ���޵���ǰ����ʱ��

// TODO������ʵ���������ϵ��
#define PC_SENSOR 2		// �����Ŵ�ϵ��
#define IC_SENSOR 1		// ���ַŴ�ϵ��
#define DC_SENSOR 2		// ΢�ַŴ�ϵ��

#define PC_MOTOR 300	// �����Ŵ�ϵ��
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

#define MOTOR_LEFT_PIN1 22	// �� 1   
#define MOTOR_LEFT_PIN2 24	// �� 2
#define MOTOR_LEFT_PIN3 26	// �� 3
#define MOTOR_LEFT_PIN4 28 	// �� 4

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

#define SENSOR_8 3
#define SENSOR_7 30
#define SENSOR_6 32
#define SENSOR_5 34
#define SENSOR_4 36
#define SENSOR_3 38
#define SENSOR_2 40	
#define SENSOR_1 2
#define numG_1 42
#define numG_2 44
#define numG_3 46
#define numO_1 48
#define numO_2 50
#define numO_3 52
#define promixSen 21

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //��������Ȩֵ
int SENSOR[] = { SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8 };
float ReadSensor();

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
/*							  ֱ�����                                  */
/************************************************************************/
#define DCmotorPin1 42 // ����I1�ӿ�
#define DCmotorPin2 43// ����I2�ӿ�
#define DCmotorPwm 4	// PWM��
#define DCSPEED 50
void dcDrive();
Servo servo_1;

/************************************************************************/
/*				              ����ͨ��                                   */
/************************************************************************/

int numG = 0;
int numO = 0;
int btOrder = -1;
String readin;
void readBTData(void);
void writeBTData(String);


/************************************************************************/
/*							����Ƭͨ��                                   */
/************************************************************************/
#define STOPDC  41
#endif

