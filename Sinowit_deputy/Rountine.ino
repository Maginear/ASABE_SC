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

void goforward(void)		//直走，时间为forwardInterval， 随后调用 afterForwardFunction（函数指针）
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

void goBack(void)		//  反方向走
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
	posflag = 0;
	Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	Timer1.start();
	Timer3.start();
	
	MsTimer2::set(1000, reSetMsTimer2);		// 进入黑线范围前直走， 结束后正常循迹
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
		//posflag++;
		ReadSensor();
		if (corner == 17 || corner == 16)
		{
			//posflag = 1;
			/*Serial2.print(crossLineTime);
			Serial2.print('+');
			Serial2.println(isHasShortGo);*/
			if (crossLineTime == 0)
				crossLineTime = 1;
			else
			{
				isHasShortGo = 1;
				forwardInterval = 500;
				afterForwardFunction = crossLine;
				goforward();
			}
			//Serial2.println(crossLineTime);
		}
	}
	else if (isHasShortGo == 1)
	{
		//Serial2.println("turn");
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
		posflag = 1;
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
			//posflag = 2;
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
		isHasShortGo = 2;
		forwardInterval = 500;
		afterForwardFunction = toCenteralLine;
		MsTimer2::set(TurnInterval, goforward);
		posflag = 2;
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
	btOrder = 0;	// 到达交接区域，准备交接 loop中开始通信
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
	MsTimer2::set(TurnInterval * 2 + 400 , backToEnd);	// 方向转过来后调用
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
	posflag = 5;
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
		posflag++;//posflag=6,7,8
		if (crossLineTime < 2)
		{
			crossLineTime++;
			if (crossLineTime == 0)
			{
				posflag = 6;
			}
			else if (crossLineTime == 1)
			{
				posflag = 7;
			}
			//writeXbeeData("x,y,g,0")
		}
		else
		{
			posflag = 8;
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
	posflag = 9;
	Timer3.start();
	Timer1.start();
	
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
	MsTimer2::set(3000, goforward);
	//MsTimer2::start();
	for (int i = 80; i < 180; i++) 
	{ 
		servo_2.write(i);
		delay(5);
	}
	
	//Serial.println("before");
	//delay(3000);
	posflag = 11;
	//goforward();
	MsTimer2::start();
	
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
	forwardInterval = 1000;
	afterForwardFunction = getBallOut_2;
	//Serial.println("after1.5");
	MsTimer2::set(TurnInterval * 2, goBack);
	posflag = 13;
	MsTimer2::start();
	//delay(TurnInterval * 2);	
	//delay(5600);
	//Serial.println("after2");
	
	/*goBack();*/
	servo_2.write(80);
	for (int i = 80; i < 180; i++)
	{
		servo_1.write(i);
		delay(5);
	}
	
}


void getBallOut_2(void)
{
	//Serial.println("after3");
	Timer1.stop();
	Timer3.stop();
	posflag = 14;
	forwardInterval = 1000;
	afterForwardFunction = stopAllTimer;
	MsTimer2::set(3000, goforward);
	//MsTimer2::start();
	// 第一个舵机打开，放出球, 3S时间
	servo_1.write(80);
	for (int i = 80; i <180; i++)
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
	Serial2.print(String(posXint) + "," + String(posYint) + "," + String(ballcolor) + "," + String(numG) + "," + String(numO) + "," + String(stoptimer) + "\r\n");
	Serial2.flush();
	Serial.print(String(posXint) + "," + String(posYint) + "," + String(ballcolor) + "," + String(numG) + "," + String(numO) + "," + String(stoptimer) + "\r\n");
	Serial.flush();
	//delay(100);
}

void posupdate()//自动生成位置信息
{
	posX = xflag*perstep + posX;
	posY = yflag*perstep + posY;
	posXint = (int)posX;
	posYint = (int)posY;
}

void test()
{
	//Timer1.attachInterrupt(DriveLeft);
	Timer3.attachInterrupt(DriveRight);
	//Timer1.setPeriod(4000);
	Timer3.setPeriod(4000);
	//Timer1.start();
	Timer3.start();
	delay(2000);
	//Timer1.attachInterrupt(BackLeft);
	Timer3.attachInterrupt(BackRight);
	delay(2000);

}
