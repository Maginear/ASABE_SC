/*
* ASABE 2016 ZJUer
* Group Sinowit
* Last Edit by Magy
* 2016/05/02
*/
#include <Servo.h>
#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>


void setup()
{
	pinMode(MOTOR_LEFT_PIN1, OUTPUT);
	pinMode(MOTOR_LEFT_PIN2, OUTPUT);
	pinMode(MOTOR_LEFT_PIN3, OUTPUT);
	pinMode(MOTOR_LEFT_PIN4, OUTPUT);
	pinMode(MOTOR_RIGHT_PIN1, OUTPUT);
	pinMode(MOTOR_RIGHT_PIN2, OUTPUT);
	pinMode(MOTOR_RIGHT_PIN3, OUTPUT);
	pinMode(MOTOR_RIGHT_PIN4, OUTPUT);
	pinMode(SENSOR_1, INPUT);
	pinMode(SENSOR_2, INPUT);
	pinMode(SENSOR_3, INPUT);
	pinMode(SENSOR_4, INPUT);
	pinMode(SENSOR_5, INPUT);
	pinMode(SENSOR_6, INPUT);
	pinMode(SENSOR_7, INPUT);
	pinMode(SENSOR_8, INPUT);

	PID_inti();
	Timer1.initialize(Stepinterval);	// 设置步进电机的初始 节拍间隔
	//Timer1.attachInterrupt(DriveLeft); // Drive Left Motor to run every stepinterval us	传入回调函数
	Timer3.initialize(Stepinterval);	// 同上
	//Timer3.attachInterrupt(DriveRight);
	//Timer1.detachInterrupt();
	//Timer3.detachInterrupt();
	
	
	//MsTimer2::set(ReadSensorInterval, updatePID); // 设置传感器扫描间隔， 以及回调函数
	//MsTimer2::start();

	//attachInterrupt(0, TurnLeft, RISING);		// 使用0号中断触发左转， 实际对应数字引脚2 (D2) ，触发条件为出现上升沿
	//attachInterrupt(1, TurnRight, RISING);		// 使用1号中断，实际对应数字引脚3 (D3), 出发条件为出现上升沿
	/*
	中断技术可参考 http://arduino.cc/en/Reference/AttachInterrupt
	LOW	当针脚输入为低时，触发中断
	CHANGE	当针脚输入发生改变时，触发中断
	RISING	当针脚输入由低变高时，触发中断
	FALLING	当针脚输入由高变低时，触发中断
	*/
	/*servo_1.attach(9);
	servo_1.write(90);
	servo_2.attach(10);
	servo_2.write(90);*/
	Serial.begin(9600);
	Serial1.begin(9600);
	//Serial1.setTimeout(100);
	/*Serial.println("setup");
	Serial.println("setup");
	Serial.println("setup"); 
	Serial.println("setup");*/
	rountine();
	//getBall();
}

void loop()
{
	switch (btOrder)
	{
	case 0:
		MsTimer2::stop();
		servo_1.write(90);//+++
		while (readin[2] != 'D' || readin[1] != '1')		// 等待对方放球完毕，传输球的颜色
		{
			readBTData();
			/*Serial1.println("S1#");
			Serial1.flush();
			Serial.println("S1");*/
			writeBTData("S1");
		}

		numG = readin[4] - '0';
		servo_1.write(-90);//+++						// 关闭第一道舵机，接收第二批球
		while (readin[2] != 'D' || readin[1] != '2')		// 等待对方放球完毕，传输球的颜色
		{
			readBTData();
			writeBTData("S2");
		}
		numO = readin[4] - '0';
		/*while (readin != "OVER")
		{
		readBTData();
		}*/
		btOrder = -1;

		MsTimer2::set(2000, goBack);
		MsTimer2::start();				// 调用回程
		break;
	default:
		break;
	}
}
