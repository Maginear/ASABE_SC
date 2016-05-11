/*
* ASABE 2016 ZJUer
* This part is used to drive stepper motor
* Last Edit by Magy
* 2016/05/02
*/
#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int right_step = 0;
int left_step = 0;
int leftOrRight = 0;		// 1Ϊ�ң�0Ϊ��
int forwardOrback = 0;		// 1Ϊǰ���� 0Ϊ����

// ��������ת��������ǰת
void TurnLeft(void)
{
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(5000);
	Timer1.start();
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(5000);
	Timer3.start();
	MsTimer2::set(TurnInterval, AfterTurn);
	MsTimer2::start();
}

// ������ǰת����������ת
void TurnRight(void)
{
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(5000);
	Timer1.start();
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(5000);
	Timer3.start();
	MsTimer2::set(TurnInterval, AfterTurn);
	MsTimer2::start();
}

// ת����ɺ���ǰ��һС��ʱ�� 
void AfterTurn(void)
{
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(4000);
	Timer1.start();
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(4000);
	Timer3.start();  
	MsTimer2::set(AfterTurnInterval, StopTurn); // ���ô�����ɨ������ �Լ��ص�����
	MsTimer2::start();
}

// ��ǰ��Ҳ��ɺ󣬻ָ������Ĵ��������²������
void StopTurn(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);
	MsTimer2::start();
}

void BackLeft(void)
{
	leftOrRight = 0;
	forwardOrback = 0;
	MotorStep();
}

void BackRight(void)
{
	leftOrRight = 1;
	forwardOrback = 0;
	MotorStep();
}

void DriveLeft(void)
{
	leftOrRight = 0;
	forwardOrback = 1;
	MotorStep();
}

void DriveRight(void)
{
	leftOrRight = 1;
	forwardOrback = 1;
	MotorStep();
}

void MotorStep(void)
{
	int Pin0, Pin1, Pin2, Pin3, thisStep = 0;
	if (leftOrRight == 0 && forwardOrback == 1)			// ���� ��ǰ
	{
		//    Pin0 = 22;
		//    Pin1 = 24;
		//    Pin2 = 26;
		//    Pin3 = 28;
		Pin0 = MOTOR_LEFT_PIN1;
		Pin1 = MOTOR_LEFT_PIN2;
		Pin2 = MOTOR_LEFT_PIN3;
		Pin3 = MOTOR_LEFT_PIN4;
		thisStep = left_step;
	}
	else if (leftOrRight == 1 && forwardOrback == 1)	// ���� ��ǰ
	{
		Pin0 = MOTOR_RIGHT_PIN1;
		Pin1 = MOTOR_RIGHT_PIN2;
		Pin2 = MOTOR_RIGHT_PIN3;
		Pin3 = MOTOR_RIGHT_PIN4;
		thisStep = right_step;
	}
	else if (leftOrRight == 0 && forwardOrback == 0)	// ���� ����
	{
		Pin0 = MOTOR_LEFT_PIN4;
		Pin1 = MOTOR_LEFT_PIN3;
		Pin2 = MOTOR_LEFT_PIN2;
		Pin3 = MOTOR_LEFT_PIN1;
		thisStep = left_step;
	}
	else												//���� ����
	{
		Pin0 = MOTOR_RIGHT_PIN4;
		Pin1 = MOTOR_RIGHT_PIN3;
		Pin2 = MOTOR_RIGHT_PIN2;
		Pin3 = MOTOR_RIGHT_PIN1;
		thisStep = right_step;
	}

	switch (thisStep)
	{
	case 0:
		digitalWrite(Pin0, HIGH);
		digitalWrite(Pin1, LOW);
		digitalWrite(Pin2, HIGH);
		digitalWrite(Pin3, LOW);//32A
		break;
	case 1:
		digitalWrite(Pin0, LOW);
		digitalWrite(Pin1, LOW);//10B
		digitalWrite(Pin2, HIGH);
		digitalWrite(Pin3, LOW);
		break;
	case 2:
		digitalWrite(Pin0, LOW);
		digitalWrite(Pin1, HIGH);
		digitalWrite(Pin2, HIGH);
		digitalWrite(Pin3, LOW);
		break;
	case 3:
		digitalWrite(Pin0, LOW);
		digitalWrite(Pin1, HIGH);
		digitalWrite(Pin2, LOW);
		digitalWrite(Pin3, LOW);
		break;
	case 4:
		digitalWrite(Pin0, LOW);
		digitalWrite(Pin1, HIGH);
		digitalWrite(Pin2, LOW);
		digitalWrite(Pin3, HIGH);
		break;
	case 5:
		digitalWrite(Pin0, LOW);
		digitalWrite(Pin1, LOW);
		digitalWrite(Pin2, LOW);
		digitalWrite(Pin3, HIGH);
		break;
	case 6:
		digitalWrite(Pin0, HIGH);
		digitalWrite(Pin1, LOW);
		digitalWrite(Pin2, LOW);
		digitalWrite(Pin3, HIGH);
		break;
	case 7:
		digitalWrite(Pin0, HIGH);
		digitalWrite(Pin1, LOW);
		digitalWrite(Pin2, LOW);
		digitalWrite(Pin3, LOW);
		break;
	default:
		digitalWrite(Pin0, LOW);
		digitalWrite(Pin1, LOW);
		digitalWrite(Pin2, LOW);
		digitalWrite(Pin3, LOW);
		break;
	}
	thisStep++;

	if (thisStep > 7)
	{
		thisStep = 0;
	}
	if (!leftOrRight)   //��ߵ��
	{
		left_step = thisStep;
	}
	else
	{
		right_step = thisStep;
	}
}
