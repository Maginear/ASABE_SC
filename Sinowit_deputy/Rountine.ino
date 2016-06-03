#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int forwardInterval = 2000;		// 向前的时间
int crossLineTime = 0;
int isHasShortGo = 0;

void rountine(void)
{
	getOut();
}

void goforward(void)		//直走，时间为forwardInterval， 随后调用 afterForwardFunction（函数指针）
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(6000);
	Timer3.setPeriod(6000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void goBack(void)		//  反方向走
{
	Timer1.attachInterrupt(BackLeft);
	Timer3.attachInterrupt(BackRight);
	Timer1.setPeriod(6000);
	Timer3.setPeriod(6000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void getOut(void)
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.stop();
	Timer3.stop();
	Timer1.setPeriod(6000);
	Timer3.setPeriod(6000);
	Timer1.start();
	Timer3.start();
	MsTimer2::set(1500, reSetMsTimer2);		// 进入黑线范围前直走， 结束后正常循迹
	MsTimer2::start();
	isHasShortGo = 0;
	crossLineTime = 0;
	attachInterrupt(0, crossLine, RISING);
}

void reSetMsTimer2(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);		//进入正常的循迹
	MsTimer2::start();
}

void crossLine(void)
{
	if (isHasShortGo == 0)
	{
		ReadSensor();
		if (corner == 17 || corner == 16)
		{	
			if (crossLineTime == 0)
				crossLineTime == 1;
			else
			{
				isHasShortGo = 1;
				forwardInterval = 500;
				afterForwardFunction = crossLine;
				goforward();
			}
		}
	}
	else if (isHasShortGo == 1)
	{
		isHasShortGo = 2;
		detachInterrupt(0);
		MsTimer2::stop();
		Timer1.attachInterrupt(BackLeft);
		Timer1.setPeriod(8000);
		Timer3.attachInterrupt(DriveRight);
		Timer3.setPeriod(8000);
		Timer3.start();
		Timer1.start();
		isHasShortGo = 2;
		forwardInterval = 500;
		afterForwardFunction = crossLine;
		MsTimer2::set(TurnInterval, goforward);	// 方向转过来后调用
		MsTimer2::start();
	}
	else
	{
		reSetMsTimer2();
		detachInterrupt(0);
		isHasShortGo = 0;
		attachInterrupt(1, toCenteralLine, RISING);
	}
}

void toCenteralLine(void)
{
	if (isHasShortGo == 0)
	{
		ReadSensor();
		if (corner == 17 || corner == 16)
		{
			isHasShortGo = 1;
			forwardInterval = 500;
			afterForwardFunction = toCenteralLine;
			goforward();
		}
	}
	else if (isHasShortGo == 1)
	{
		detachInterrupt(1);
		Timer1.attachInterrupt(DriveLeft);		// 右转进入
		Timer1.setPeriod(8000);
		Timer3.attachInterrupt(BackRight);
		Timer3.setPeriod(8000);
		Timer1.start();
		Timer3.start();
		isHasShortGo == 2;
		forwardInterval = 500;
		afterForwardFunction = toCenteralLine;
		MsTimer2::set(TurnInterval, goforward);
		MsTimer2::start();
	}
	else 
	{
		reSetMsTimer2();
		crossLineTime = 0;
		isHasShortGo = 0;
		attachInterrupt(0, toDock, RISING);
	}
}

void toDock(void)
{
	ReadSensor();
	if (corner == 17 || corner == 16)
	{
		detachInterrupt(0);
		forwardInterval = 500;
		afterForwardFunction = getBall;
		goforward();
	}
}

void getBall(void)
{
	MsTimer2::stop();
	Timer1.stop();
	Timer3.stop();
	forwardInterval = 1000;
	afterForwardFunction = TurnAround;
	MsTimer2::set(2000, goBack);
}

void TurnAround(void)			// 旋转一周
{
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	Timer1.start();

	MsTimer2::set(TurnInterval * 2, backToEnd);	// 方向转过来后调用
	MsTimer2::start();

}

void backToEnd(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(6000);
	Timer3.setPeriod(6000);
	Timer1.start();
	Timer3.start();
	reSetMsTimer2();
	crossLineTime = 0;
	attachInterrupt(0, toEnd, RISING);
}

void toEnd(void)
{
	ReadSensor();
	if (corner == 17 || corner == 16)
	{
		if (crossLineTime < 3)
		{
			crossLineTime++;
		}
		else
		{
			stopAllTimeer;
		}
	}
}

void stopAllTimeer(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.stop();
	Timer3.stop();
	MsTimer2::stop();
}
