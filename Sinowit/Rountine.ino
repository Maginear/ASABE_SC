#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int forwardInterval = 1000;		// 向前的时间

void rountine(void)
{
	pickBall();
}

void reSetMsTimer2(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);		//进入正常的循迹
	MsTimer2::start();
}

void goforward(void)		//直走，时间为forwardInterval， 随后调用 afterForwardFunction（函数指针）
{
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(3000);
	Timer3.setPeriod(3000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void goBack(void)		//  反方向走
{
	Timer1.attachInterrupt(BackLeft);
	Timer3.attachInterrupt(BackRight);
	Timer1.setPeriod(3000);
	Timer3.setPeriod(3000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void pickBall(void)		
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.setPeriod(3000);
	Timer3.setPeriod(3000);
	MsTimer2::set(500, reSetMsTimer2);		// 进入黑线范围前直走， 结束后正常循迹
	MsTimer2::start();
	forwardInterval = 1000;					
	afterForwardFunction = stopTimer13;		// 走到球前面时，调用
	attachInterrupt(0, goforward, RISING);	//当到达第一个转折，不转弯，直走去取第一个球
}


void stopTimer13(void)		// 不动，用于捡球
{
	Timer1.stop();
	Timer3.stop();
	afterForwardFunction = turnLeft_in_ball;
	forwardInterval = 1000;
	MsTimer2::set(5000, goforward);			//捡球完成后，向前走一段路，再左转
	MsTimer2::start();	
}

void turnLeft_in_ball(void)
{
	MsTimer2::stop();
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(8000);
	Timer1.start();
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	forwardInterval = 10000;		//正常贴墙走
	afterForwardFunction = turn_Out_ball;
	MsTimer2::set(TurnInterval, goforward);
	MsTimer2::start();
}

void turn_Out_ball(void)		// 左轮不动，右轮倒转，车身离开墙面
{
	MsTimer2::stop();
	/*Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer1.start();*/
	Timer1.stop();
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	forwardInterval = 1000;
	afterForwardFunction = TurnAround;
	MsTimer2::set(TurnInterval * 2, goBack);
	MsTimer2::start();
}

void TurnAround(void)			// 旋转一周
{
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer1.start();
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	attachInterrupt(0, TurnLeft, RISING);		 
	MsTimer2::set(TurnInterval * 2, backToLine);	// 方向转过来后调用 
	MsTimer2::start();
}

void backToLine(void)
{
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	Timer1.start();
	Timer3.start();
	attachInterrupt(0, TurnLeft, RISING);
	attachInterrupt(3, Stop, RISING);			//接近开关触发，停止运动
}

void Stop(void)
{
	Timer1.stop();
	Timer3.stop();
	MsTimer2::stop();
}

