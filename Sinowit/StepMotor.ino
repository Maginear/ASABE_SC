/*
* ASABE 2016 ZJUer
* This part is used to drive stepper motor
* Last Edit by Magy
* 2016/05/04
*/
#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int right_step = 0;
int left_step = 0;
int leftOrRight = 0;		// 1为右，0为左
int forwardOrback = 0;		// 1为前进， 0为后退

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
	if (leftOrRight == 0 && forwardOrback == 1)			// 左轮 往前
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
	else if (leftOrRight == 1 && forwardOrback == 1)	// 右轮 往前
	{
		Pin0 = MOTOR_RIGHT_PIN1;
		Pin1 = MOTOR_RIGHT_PIN2;
		Pin2 = MOTOR_RIGHT_PIN3;
		Pin3 = MOTOR_RIGHT_PIN4;
		thisStep = right_step;
	}
	else if (leftOrRight == 0 && forwardOrback == 0)	// 左轮 往后
	{
		Pin0 = MOTOR_LEFT_PIN4;
		Pin1 = MOTOR_LEFT_PIN3;
		Pin2 = MOTOR_LEFT_PIN2;
		Pin3 = MOTOR_LEFT_PIN1;
		thisStep = left_step;
	}
	else												//右轮 往后
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
	//Serial.println(thisStep);
	if (thisStep > 7)	// 8个节拍循环
	{
		thisStep = 0;
	}
	if (!leftOrRight)	//左边电机
	{
		left_step = thisStep;
	}
	else
	{
		right_step = thisStep;
	}
}
