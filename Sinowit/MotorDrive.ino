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
int leftOrRight = 0;

void DriveLeft(void)
{
	leftOrRight = 0;
	MotorStep();
}

void DriveRight(void)
{
	leftOrRight = 1;
	MotorStep();
}

void MotorStep()
{
	int Pin0, Pin1, Pin2, Pin3, thisStep = 0;
	if (leftOrRight)   //左边电机
	{
		//    Pin0 = 22;
		//    Pin1 = 24;
		//    Pin2 = 26;
		//    Pin3 = 28;
		Pin0 = motor_left_pin1;
		Pin1 = motor_left_pin2;
		Pin2 = motor_left_pin3;
		Pin3 = motor_left_pin4;
		thisStep = left_step;
	}
	else
	{
		Pin0 = motor_right_pin1;
		Pin1 = motor_right_pin2;
		Pin2 = motor_right_pin3;
		Pin3 = motor_right_pin4;
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


	if (leftOrRight)   //左边电机
	{
		left_step = thisStep;
	}
	else
	{
		right_step = thisStep;
	}
}
