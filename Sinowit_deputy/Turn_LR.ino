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
	//	//TurnLeft();		// ���߶��к���;
	//	break;
	//case 16:
	//	//TurnLeft();		// ������к���
	//	break;
	//case 1:
	//	//TurnRight();	// ���ұ��к���
	//	break;

// ��������ת��������ǰת
void TurnLeft(void)
{
	MsTimer2::stop();
	ReadSensor();		//����cornerֵ��ȷ�ϴ�������ֵ�����ǵ�·���ϳ����ж�
	if (corner == 17 || corner == 16)
	{
		detachInterrupt(0);	//ȥ������ת���ж�
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

// ������ǰת����������ת
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

// ת����ɺ���ǰ��һС��ʱ�� 
void AfterTurn(void)
{
	MsTimer2::stop();
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



