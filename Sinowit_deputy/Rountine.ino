#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

int forwardInterval = 2000;		// ��ǰ��ʱ��
int crossLineTime = 0;
int isHasShortGo = 0;

void rountine(void)
{
	//Serial.println("rountine");
	Timer1.detachInterrupt();
	Timer3.detachInterrupt();
	MsTimer2::stop();
	Serial.begin(9600);
	Serial1.begin(9600);
	while (readin != "ST")
	{
		readBTData();
		Serial.println("ready!");
		Serial.flush();
		writeXbeeData();
	}
	//posflag=0;
	/*while(readin!="")*/
	/*Serial1.print("B#");
	Serial1.flush();*/
	Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	getOut();
	//getBall();
	
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
	Timer1.start();
	Timer3.start();
	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void goBack(void)		//  ��������
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.attachInterrupt(BackLeft);
	Timer3.attachInterrupt(BackRight);
	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	Timer1.start();
	Timer3.start();
	MsTimer2::set(forwardInterval, afterForwardFunction);
	MsTimer2::start();
}

void getOut(void)
{
	MsTimer2::stop();
	detachInterrupt(0);
	detachInterrupt(1);

	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	Timer1.start();
	Timer3.start();
	posflag=0;
	MsTimer2::set(1000, reSetMsTimer2);		// ������߷�Χǰֱ�ߣ� ����������ѭ��
	MsTimer2::start();
	isHasShortGo = 0;
	crossLineTime = 0;
	attachInterrupt(0, crossLine, RISING);
}

void reSetMsTimer2(void)
{
	MsTimer2::set(ReadSensorInterval, updatePID);		//����������ѭ��
	MsTimer2::start();
}

void crossLine(void)
{
	if (isHasShortGo == 0)
	{
		//posflag++;
		ReadSensor();
		if (corner == 17 || corner == 16)
		{
			posflag = 1;
			if (crossLineTime == 0)
				crossLineTime = 1;
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
		MsTimer2::set(TurnInterval, goforward);	// ����ת���������
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
		if (corner == 17 || corner == 16 || corner == 1)
		{
			posflag = 2;
			isHasShortGo = 1;
			forwardInterval = 500;
			afterForwardFunction = toCenteralLine;
			goforward();
		}
	}
	else if (isHasShortGo == 1)
	{
		detachInterrupt(1);
		Timer1.attachInterrupt(DriveLeft);		// ��ת����
		Timer1.setPeriod(8000);
		Timer3.attachInterrupt(BackRight);
		Timer3.setPeriod(8000);
		Timer1.start();
		Timer3.start();
		isHasShortGo = 2;
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
		posflag = 3;
		detachInterrupt(0);
		forwardInterval = 1300;
		afterForwardFunction = getBall;
		goforward();
	}
}

void getBall(void)
{
	MsTimer2::stop();
	Timer1.stop();
	Timer3.stop();
	Timer1.detachInterrupt();
	Timer3.detachInterrupt();
	/*Timer1.start();
	Timer3.start();*/
	Serial.begin(9600);
	Serial1.begin(9600);
	
	forwardInterval = 1500;
	afterForwardFunction = TurnAround;
	posflag = 4;
	btOrder = 0;	// ���ｻ������׼������ loop�п�ʼͨ��
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
	MsTimer2::set(TurnInterval * 2 + 400 , backToEnd);	// ����ת���������
	MsTimer2::start();
}

void backToEnd(void)
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
	posflag = 5;
	reSetMsTimer2();
	crossLineTime = 0;
	attachInterrupt(0, toEnd, RISING);
}

void toEnd(void)
{
	ReadSensor();
	if (corner == 17 || corner == 16)
	{
		posflag++;//posflag=6,7,8
		if (crossLineTime < 2)
		{
			crossLineTime++;
			
			//writeXbeeData("x,y,g,0")
		}
		else
		{
			MsTimer2::stop();
			detachInterrupt(0);
			forwardInterval = 1600;
			afterForwardFunction = unpack;
			goforward();
		}
	}
}

void unpack(void)
{
	detachInterrupt(0);
	detachInterrupt(1);
	MsTimer2::stop();
	Timer1.attachInterrupt(BackLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(DriveRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	Timer1.start();
	posflag = 9;
	forwardInterval = 1000;
	afterForwardFunction = getBallOut_1;
	MsTimer2::set(TurnInterval, goBack);
	MsTimer2::start();
}

void getBallOut_1(void)
{
	MsTimer2::stop();
	Timer1.stop();
	Timer3.stop();
	posflag = 10;
	forwardInterval = 1000;
	afterForwardFunction = Turn360;
	//MsTimer2::set(3000, goforward);
	//MsTimer2::start();
	for (int i = 80; i > 0; i--) 
	{ 
		servo_2.write(i);
		delay(5);
	}
	//MsTimer2::start();
	//Serial.println("before");
	delay(3000);
	posflag = 11;
	goforward();
	
}

void Turn360(void)
{
	posflag = 12;
	//Serial.println("after");
	MsTimer2::stop();
	Timer1.attachInterrupt(DriveLeft);
	Timer1.setPeriod(8000);
	Timer3.attachInterrupt(BackRight);
	Timer3.setPeriod(8000);
	Timer3.start();
	Timer1.start();
	forwardInterval = 2000;
	afterForwardFunction = getBallOut_2;
	//MsTimer2::set(TurnInterval * 2, goBack);
	//MsTimer2::start();
	delay(TurnInterval * 2);
	posflag = 13;
	goBack();
	servo_2.write(80);
	for (int i = 95; i > 0; i--)
	{
		servo_1.write(i);
		delay(5);
	}
	
}


void getBallOut_2(void)
{
	Timer1.stop();
	Timer3.stop();
	posflag = 14;
	forwardInterval = 1000;
	afterForwardFunction = stopAllTimer;
	MsTimer2::set(3000, goforward);
	//MsTimer2::start();
	// ��һ������򿪣��ų���, 3Sʱ��
	servo_1.write(95);
	for (int i = 80; i > 0; i--)
	{
		servo_2.write(i);
		delay(5);
	}
	MsTimer2::start();
}

void stopAllTimer(void)
{
	servo_2.write(80);	
	detachInterrupt(0);
	detachInterrupt(1);
	Timer1.stop();
	Timer3.stop();
	MsTimer2::stop();
}

void writeXbeeData()
{
	Serial2.print(String(posX) + "," + String(posY) + "," + String(ballcolor) + "," + String(numG) + "," + String(numO) + "," + String(stoptimer) + "\r\n");
	Serial2.flush();
	Serial.print(String(posX) + "," + String(posY) + "," + String(ballcolor) + "," + String(numG) + "," + String(numO) + "," + String(stoptimer) + "\r\n");
	Serial.flush();
	//delay(100);
}

void posupdate()//�Զ�����λ����Ϣ
{
	posX = xflag*perstep + posX;
	posY = yflag*perstep + posY;
}