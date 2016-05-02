/*
* ASABE 2016 ZJUer
* Group Sinowit
* Last Edit by Magy
* 2016/05/02
*/
#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>



typedef struct p
{
	float  error_1;	// �ϴε����
	float sumerror;	// �ۻ����
} PID;
PID Pid;
PID* pid = &Pid;
int pidOut = 0;                 // pid�����ֵ

void PID_inti()//PID��ʼ��
{
	pid->error_1 = 0;
	pid->sumerror = 0;
}



int  PIDCal(float error)//PID���㡣λ��ʽ��
{
	float output, derror;

	pid->sumerror += error;

	derror = (error - pid->error_1);

	output = error * PC + pid->sumerror * IC + derror * DC;

	pid->error_1 = error;
	return (int)(output + 0.5);
}

void updatePID(void)
{
	float senVal = ReadSensor();
	//  Serial.print("senVal:" );
	//  Serial.println(senVal);
	pidOut = PIDCal(senVal);

	MotorAdjust(pidOut);
}

int steplimit(int stepnum)
{
	if (stepnum > MAX)
		stepnum = MAX;
	if (stepnum < MIN)
		stepnum = MIN;
	return stepnum;
}

void MotorAdjust(int pidOut)
{
	int l_step = Stepinterval;
	int r_step = Stepinterval;
	if (pidOut != 0)
	{
		l_step = Basic_Left - pidOut;
		r_step = Basic_Right + pidOut;
		l_step = steplimit(l_step);
		r_step = steplimit(r_step);
		int stepSum = l_step + r_step;
		l_step = l_step * 10 / stepSum;
		r_step = r_step * 10 / stepSum;
	}
	Timer1.setPeriod(l_step * 1000);  // ����������Ľ���ʱ����
	Timer3.setPeriod(r_step * 1000);
}