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

	//case 17:
	//	//TurnLeft();		// 两边都有黑心;
	//	break;
	//case 16:
	//	//TurnLeft();		// 最左边有黑线
	//	break;
	//case 1:
	//	//TurnRight();	// 最右边有黑线
	//	break;

// 左轮往后转，右轮往前转
void TurnLeft(void)
{
	MsTimer2::stop();
	
	ReadSensor();		//更新corner值，确认传感器的值，而非电路故障出现中断
	if (corner == 17 || corner == 16)
	{
		detachInterrupt(0);	//去除左右转的中断
		detachInterrupt(1);
		//detachInterrupt(2);
		MsTimer2::stop();
		Timer1.attachInterrupt(BackLeft);
		Timer1.setPeriod(8000);
		Timer1.start();
		Timer3.attachInterrupt(DriveRight);
		Timer3.setPeriod(8000);
		Timer3.start();
		MsTimer2::set(TurnInterval, AfterTurn);
		MsTimer2::start();
	}
	else
	{
		MsTimer2::start();
	}
}

// 左轮往前转，右轮往后转
void TurnRight(void)
{
	MsTimer2::stop();
	ReadSensor();
	if (corner == 1)
	{
		detachInterrupt(0);
		detachInterrupt(1);
		//detachInterrupt(2);

		MsTimer2::stop();
		Timer1.attachInterrupt(DriveLeft);
		Timer1.setPeriod(8000);
		Timer1.start();
		Timer3.attachInterrupt(BackRight);
		Timer3.setPeriod(8000);
		Timer3.start();
		MsTimer2::set(TurnInterval, AfterTurn);
		MsTimer2::start();
	}
	else
	{
		MsTimer2::start();
	}
}

// 转弯完成后，往前走一小段时间 
void AfterTurn(void)
{
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(4000);
	Timer1.start();
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(4000);
	Timer3.start();
	MsTimer2::set(AfterTurnInterval, StopTurn); // 设置传感器扫描间隔， 以及回调函数
	MsTimer2::start();
}

// 往前走也完成后，恢复正常的传感器更新步进电机
void StopTurn(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);
	MsTimer2::start();
	attachInterrupt(0, Stop, RISING);			//接近开关触发，停止运动
}



