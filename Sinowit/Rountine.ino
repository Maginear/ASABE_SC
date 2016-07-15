#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int forwardInterval = 2000;		// ��ǰ��ʱ��
int leftInterruptTimeInLast = 0;

void rountine(void)
{
	pickBall();
	//backToLine();
	//haveABreak();
	//GoWithNoLeft();
}

void goforward(void)		//ֱ�ߣ�ʱ��ΪforwardInterval�� ������ afterForwardFunction������ָ�룩
{
	MsTimer2::stop();
	detachInterrupt(0); 
	detachInterrupt(1);
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	
	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void goBack(void)		//ֱ�ߣ�ʱ��ΪforwardInterval�� ������ afterForwardFunction������ָ�룩
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.attachInterrupt(BackLeft);
	Timer3.attachInterrupt(BackRight);
	Timer1.setPeriod(6000);
	Timer3.setPeriod(6000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void getOut(void)		//  ��������
{
	Timer1.attachInterrupt(BackLeft);
	Timer3.attachInterrupt(BackRight);
	Timer1.setPeriod(6000);
	Timer3.setPeriod(6000);

	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void pickBall(void)
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.stop();
	Timer3.stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	Timer1.start();
	Timer3.start();
	MsTimer2::set(1000, reSetMsTimer2);		// ������߷�Χǰֱ�ߣ�����������ѭ��
	MsTimer2::start();
}

void reSetMsTimer2(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);		//����������ѭ��
	MsTimer2::start();
	forwardInterval = 2000;
	afterForwardFunction = TurnLeft_45_Degree;		// �ߵ���ǰ��ʱ������
	                                     //��ʼ����
	attachInterrupt(0, goforward, RISING);	//�������һ��ת�ۣ���ת�䣬ֱ��ȥȡ��һ����
}

void TurnLeft_45_Degree(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	MsTimer2::stop();
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer1.start();
	Timer3.start();
	dcDrive();
	if (turn_45_times == 0)
	{
		forwardInterval = 600;
		turn_45_times++;
		afterForwardFunction = TurnLeft_45_Degree;
		MsTimer2::set(HalfTurnInterval, goforward);
		MsTimer2::start();
	}
	else
	{
		forwardInterval = 11000;
		afterForwardFunction = turn_Out_ball;
		MsTimer2::set(HalfTurnInterval, goforward_onWall);
		MsTimer2::start();
	}
}

void goforward_onWall(void)		//ֱ�ߣ�ʱ��ΪforwardInterval�� ������ afterForwardFunction������ָ�룩
{
	MsTimer2::stop();
	//stopservo = 1;
	detachInterrupt(0);
	detachInterrupt(1);
	//attachInterrupt(digitalPinToInterrupt(18),color_sort,RISING);
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	Timer1.setPeriod(5800);
	Timer3.setPeriod(6200);
	Timer1.start();
	Timer3.start();
	
	
	//stopservo = 2;
	MsTimer2::set(forwardInterval, incline);
	MsTimer2::start();
}

void incline()
{
	MsTimer2::stop();
	Timer1.setPeriod(6400);
	Timer3.setPeriod(5800);

	MsTimer2::set(5000, afterForwardFunction); //б�߳���
	MsTimer2::start();
}

void TurnLeft_90()
{
	MsTimer2::stop();
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer1.start();
	Timer3.start();
	forwardInterval = 2000;
	MsTimer2::set(HalfTurnInterval, goforward);
	MsTimer2::start();

}

//void stopTimer13(void)		// ���������ڼ���
//{
//	Timer1.stop();
//	Timer3.stop();
//	afterForwardFunction = turnLeft_in_ball;
//	forwardInterval = 1000;
//	MsTimer2::set(3000, goforward);			//������ɺ���ǰ��һ��·������ת
//	MsTimer2::start();
//}
//
//void turnLeft_in_ball(void)
//{
//	MsTimer2::stop();
//	Timer1.attachInterrupt(BackLeft);
//	Timer1.setPeriod(8000);
//	Timer3.attachInterrupt(DriveRight);
//	Timer3.setPeriod(8000);
//	Timer1.start();
//	Timer3.start();
//	forwardInterval = 15000;		//������ǽ��
//	afterForwardFunction = turn_Out_ball;
//	MsTimer2::set(TurnInterval, goforward);
//	MsTimer2::start();
//}

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
	forwardInterval = 1000;
	afterForwardFunction = TurnAround;
	MsTimer2::set(TurnInterval * 2+600, goBack);
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
	MsTimer2::stop();
	Timer1.detachInterrupt();
	Timer3.detachInterrupt();
	/*Timer1.start();
	Timer3.start();*/
	btOrder = 0;
	digitalWrite(STOPDC, HIGH);
	/*Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer1.stop();
	Timer3.stop();*/
	
	//Stop();
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
	attachInterrupt(0, face_the_line, RISING);
	attachInterrupt(1, face_the_line, RISING);
	afterFaceTheLineFunc = TurnLeft_spe;
	
}
void face_the_line()
{
	ReadSensor();
	if (corner != 0)
	{
		MsTimer2::stop();
		detachInterrupt(0);
		detachInterrupt(1);
		Timer1.detachInterrupt();
		Timer3.detachInterrupt();
		Timer1.stop();
		Timer3.stop();
		Serial.begin(9600);
		Serial1.begin(9600);
		

		ReadSensor();
		if (corner == 1)
		{
			Timer1.setPeriod(4000);
			Timer1.attachInterrupt(DriveLeft);
			Timer3.setPeriod(10400);
			Timer3.attachInterrupt(BackRight);
			Timer1.start();
			Timer3.start();
			attachInterrupt(0, afterFaceTheLineFunc, RISING);
		}
		else if (corner == 16)
		{
			Timer1.setPeriod(10400);
			Timer1.attachInterrupt(BackLeft);
			Timer3.setPeriod(4000);
			Timer3.attachInterrupt(DriveRight);
			Timer1.start();
			Timer3.start();
			attachInterrupt(1, afterFaceTheLineFunc, RISING);
		}
		else
		{
			afterFaceTheLineFunc();
		}
	}
	else
	{
		Timer1.start();
		Timer3.start();
	}
}

void TurnLeft_spe(void)
{
	
	ReadSensor();
	if (corner == 17 || corner == 16)
	{
		MsTimer2::stop();
		detachInterrupt(0);
		detachInterrupt(1);
		Timer1.stop();
		Timer3.stop();

		Timer1.attachInterrupt(BackLeft);
		Timer1.setPeriod(8000);
		Timer3.attachInterrupt(DriveRight);
		Timer3.setPeriod(8000);
		Timer1.start();
		Timer3.start();
		forwardInterval = 500;
		afterForwardFunction = GoWithNoLeft;
		MsTimer2::set(TurnInterval, goforward);
		MsTimer2::start();
	}
}

void GoWithNoLeft(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	attachInterrupt(1, TurnRight, RISING);
	Serial.println("ss");
	MsTimer2::set(ReadSensorInterval, updatePID);		//����������ѭ��
	MsTimer2::start();
}

void Stop(void)
{
	Timer1.stop();
	Timer3.stop();
	MsTimer2::stop();
	Serial.println("Stop end");
	btOrder = 1;		// �Ѿ���λ����ʼloop����ĶԽ�	

}
void readnum()
{
	numG =digitalRead( numG_1 )+ digitalRead(numG_2) * 2 + digitalRead(numG_3) * 4;
	numO = digitalRead(numO_1) + digitalRead(numO_3) * 2 + digitalRead(numO_3) * 4;
}