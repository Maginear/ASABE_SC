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
#define Stepinterval 4000    //�������ÿ������֮���ʱ�� 4ms
#define ReadSensorInterval 10000  //���⴫�����Ķ�ȡ���ʱ��

// TODO������ʵ���������ϵ��
#define PC 2  // �����Ŵ�ϵ��
#define IC 2    //���ַŴ�ϵ��
#define DC 6    //��ϵ��

#define Basic_Left  50 //�岽 ���ڻ�鵽10��
#define Basic_Right 50 //
#define MAX 100
#define MIN 0

/************************************************************************/
/*					�����ǲ�������Ĳ���                                 */
/************************************************************************/
// change this to the number of steps on your motor
#define STEPS 400 //��Ϊ��8�ģ� ����360 / 0.9

#define motor_left_pin1 28
#define motor_left_pin2 26
#define motor_left_pin3 24
#define motor_left_pin4 22

#define motor_right_pin1 36
#define motor_right_pin2 34
#define motor_right_pin3 32
#define motor_right_pin4 30


/************************************************************************/
/*                 �����Ǵ������Ĳ���                                    */
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

int weight[] = { -10, -8, -4, -2, 2, 4, 8, 10 }; //��������Ȩֵ
int sensor[] = { sensor_1, sensor_2, sensor_3, sensor_4, sensor_5, sensor_6, sensor_7, sensor_8 };

#endif

