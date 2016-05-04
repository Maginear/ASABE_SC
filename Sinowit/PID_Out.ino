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

PID Pid_sensor, Pid_motor_l, Pid_motor_r;

PID* pid_sensor = &Pid_sensor;
PID* pid_m_l = &Pid_motor_l;
PID* pid_m_r = &Pid_motor_r;
int pid_interval = 0;

void PID_inti()//PID初始化
{
	pid_sensor->error_1 = 0;
	pid_sensor->sumerror = 0;
	pid_sensor->pc = PC_SENSOR;
	pid_sensor->ic = IC_SENSOR;
	pid_sensor->dc = DC_SENSOR;
	pid_m_l->error_1 = 0;
	pid_m_l->sumerror = 0;
	pid_m_l->pc = PC_MOTOR;
	pid_m_l->ic = IC_MOTOR;
	pid_m_l->dc = DC_MOTOR;
	pid_m_r->error_1 = 0;
	pid_m_r->sumerror = 0;
	pid_m_r->pc = PC_MOTOR;
	pid_m_r->ic = IC_MOTOR;
	pid_m_r->dc = DC_MOTOR;
}

int PIDCal(PID* pid, float error)	//PID计算。位置式。
{
	float output, derror;
	if (pid_interval == 0)
		pid->sumerror += error;
	pid_interval++;
	if (pid_interval == 5)
		pid_interval = 0;

	if (pid->sumerror < -20)
		pid->sumerror = -20;
	else if (pid->sumerror > 20)
		pid->sumerror = 20;

	derror = (error - pid->error_1);

	output = error * pid->pc + pid->sumerror * pid->ic + derror * pid->dc;

	pid->error_1 = error;
	return (int)(output + 0.5);
}

void updatePID(void)
{
	float senVal = ReadSensor();
	if (senVal == 0)
		pid_sensor->sumerror = 0;
	Serial.print("senVal:" );
	Serial.println(senVal);
	switch (corner)
	{
	case 0x11:
		TurnLeft();		// 两边都有黑心;
		break;
	case 0x10:
		TurnLeft();		// 最左边有黑线，corner = 1
		break;
	case 0x01:
		TurnRight();	// 最右边有黑线，corner = 2
		break;
	default:
		corner = 0;		// 左右两端传感器无黑线 corner = 0;
		break;
	}

    // pid的输出值
	int pidOut = PIDCal(pid_sensor, senVal);
	MotorAdjust(pidOut);
}

int steplimit(int stepnum, int max, int min)
{
	if (stepnum > max)
		stepnum = max;
	if (stepnum < min)
		stepnum = min;
	return stepnum;
}

void MotorAdjust(int pidOut)
{
	Serial.print("motor pidout: ");
	Serial.println(pidOut);
	int l_step = Stepinterval;
	int r_step = Stepinterval;
	if (pidOut != 0)
	{
		l_step = Basic_Left - pidOut;
		r_step = Basic_Right + pidOut;
		l_step = steplimit(l_step, 175, 25);
		r_step = steplimit(r_step, 175, 25);
		int stepSum = l_step + r_step;
		l_step = l_step * 10 / stepSum;
		r_step = r_step * 10 / stepSum;
		Serial.println(l_step);
		Serial.println(r_step);
	}
	int l = PIDCal(pid_m_l, l_step);
	int r = PIDCal(pid_m_r, r_step);
	l = steplimit(l, 4000, 0);
	r = steplimit(r, 4000, 0);
	Serial.println(l);
	Serial.println(r);
	Timer1.setPeriod(l + 4000);  // 更新左侧电机的节拍时间间隔
	Timer3.setPeriod(r + 4000);
	//Timer1.setPeriod(8000);	 // 更新左侧电机的节拍时间间隔
	//Timer3.setPeriod(8000);
}
