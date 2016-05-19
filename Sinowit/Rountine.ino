#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int forwardInterval = 1000;		// ��ǰ��ʱ��

void rountine(void)
{
	pickBall();
}

void reSetMsTimer2(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);		//����������ѭ��
	MsTimer2::start();
	forwardInterval = 1700;
	afterForwardFunction = stopTimer13;		// �ߵ���ǰ��ʱ������
	attachInterrupt(0, goforward, RISING);	//�������һ��ת�ۣ���ת�䣬ֱ��ȥȡ��һ����
}

void goforward(void)		//ֱ�ߣ�ʱ��ΪforwardInterval�� ������ afterForwardFunction������ָ�룩
{
	MsTimer2::stop();
	detachInterrupt(0);
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(3000);
	Timer3.setPeriod(3000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void goBack(void)		//  ��������
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
	MsTimer2::set(1000, reSetMsTimer2);		// ������߷�Χǰֱ�ߣ� ����������ѭ��
	MsTimer2::start();
}

void stopTimer13(void)		// ���������ڼ���
{
	Timer1.stop();
	Timer3.stop();
	afterForwardFunction = turnLeft_in_ball;
	forwardInterval = 500;
	MsTimer2::set(3000, goforward);			//������ɺ���ǰ��һ��·������ת
	MsTimer2::start();
}

void turnLeft_in_ball(void)
{
	MsTimer2::stop();
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer1.start();
	Timer3.start();
	forwardInterval = 8000;		//������ǽ��
	afterForwardFunction = turn_Out_ball;
	MsTimer2::set(TurnInterval, goforward);
	MsTimer2::start();
}

void turn_Out_ball(void)		// ���ֲ��������ֵ�ת�������뿪ǽ��
{
	MsTimer2::stop();
	/*Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer1.start();*/
	Timer1.stop();
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	//forwardInterval = 500;
	//afterForwardFunction = TurnAround;
	MsTimer2::set(TurnInterval * 2, TurnAround);
	MsTimer2::start();
}

void TurnAround(void)			// ��תһ��
{
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	Timer1.start();
	
	MsTimer2::set(TurnInterval * 2, haveABreak);	// ����ת��������� 
	MsTimer2::start();
}

void haveABreak(void)
{
	Timer1.stop();
	Timer3.stop();
	MsTimer2::set(1000, backToLine);
	MsTimer2::start();
}

void backToLine(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	Timer1.start();
	Timer3.start();
	attachInterrupt(0, TurnLeft_spe, RISING);
}

void TurnLeft_spe(void)
{
	detachInterrupt(0);
	MsTimer2::stop();
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(8000);
	Timer1.start();
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	MsTimer2::set(TurnInterval, GoWithNoLeft);
	MsTimer2::start(); 
}

void GoWithNoLeft(void)
{
	detachInterrupt(0);
	attachInterrupt(1, TurnRight, RISING);
	attachInterrupt(3, Stop, RISING);			//�ӽ����ش�����ֹͣ�˶�
	MsTimer2::set(ReadSensorInterval, updatePID);		//����������ѭ��
	MsTimer2::start();
}

void Stop(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.stop();
	Timer3.stop();
	MsTimer2::stop();
}

