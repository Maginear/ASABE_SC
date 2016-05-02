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

void PID_inti()//PID初始化
{
	pid_sensor->error_1 = 0;
	pid_sensor->sumerror = 0;
	pid_sensor->pc = PC_sensor;
	pid_sensor->ic = IC_sensor;
	pid_sensor->dc = DC_sensor;
	pid_m_l->error_1 = 0;
	pid_m_l->sumerror = 0;
	pid_m_l->pc = PC_motor;
	pid_m_l->ic = IC_motor;
	pid_m_l->dc = DC_motor;
	pid_m_r->error_1 = 0;
	pid_m_r->sumerror = 0;
	pid_m_r->pc = PC_motor;
	pid_m_r->ic = IC_motor;
	pid_m_r->dc = DC_motor;
}

int PIDCal(PID* pid, float error)	//PID计算。位置式。
{
	float output, derror;

	pid->sumerror += error;
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
	int pidOut = 0;                 // pid的输出值
	pidOut = PIDCal(pid_sensor, senVal);
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
	Serial.print("motor pidout: ");
	Serial.println(pidOut);
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
	int l = steplimit(PIDCal(pid_m_l, l_step * 5));
	int r = steplimit(PIDCal(pid_m_r, r_step * 5));
	Serial.println(l);
	Serial.println(r);
	Timer1.setPeriod(l*10 + 2000);  // 更新左侧电机的节拍时间间隔
	Timer3.setPeriod(r*10 + 2000);
	//Timer1.setPeriod(8000);  // 更新左侧电机的节拍时间间隔
	//Timer3.setPeriod(8000);
}
