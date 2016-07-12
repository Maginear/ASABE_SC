
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

//Servo colorservo;
//int g_count = 0;
//int array1[3];
//int array2[3];
//int ballcolor = 0;
//int g_flag = 0;
//int time1 = 0;
//int det;
//int pos = 0;
//int stopservo = 2;
//bool whether = 0;

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
	pinMode(DCmotorPin1, OUTPUT);
	pinMode(DCmotorPin2, OUTPUT);
	pinMode(DCmotorPwm, OUTPUT);
	pinMode(numG_1, INPUT);
	pinMode(numG_2, INPUT);
	pinMode(numG_3, INPUT);
	pinMode(numO_1, INPUT);
	pinMode(numO_2, INPUT);
	pinMode(numO_3, INPUT);
	pinMode(STOPDC, OUTPUT);
	digitalWrite(STOPDC, LOW);

	//TSC_Init();
	//colorservo.attach(13);  // attaches the servo on pin 13 to the servo object
	//Serial.begin(9600);
	//attachInterrupt(digitalPinToInterrupt(18), TSC_Count, RISING);
	//delay(10);
	//for (pos = 00; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
	//	// in steps of 1 degree
	//	colorservo.write(pos);              // tell servo to go to position in variable 'pos'
	//	delay(3);                       // waits 15ms for the servo to reach the position
	//}

	dcDrive();
	servo_1.write(100);
	

	PID_inti();
	Timer1.initialize(Stepinterval);	// 设置步进电机的初始 节拍间隔
	Timer1.attachInterrupt(DriveLeft); // Drive Left Motor to run every stepinterval us	传入回调函数
	Timer3.initialize(Stepinterval);	// 同上
	Timer3.attachInterrupt(DriveRight);
	
	MsTimer2::set(ReadSensorInterval, updatePID); // 设置传感器扫描间隔， 以及回调函数
	MsTimer2::start();

	//attachInterrupt(0, TurnLeft, RISING);		// 使用0号中断触发左转， 实际对应数字引脚2 (D2) ，触发条件为出现上升沿
	//attachInterrupt(1, TurnRight, RISING);		// 使用1号中断，实际对应数字引脚3 (D3), 出发条件为出现上升沿
	Timer1.detachInterrupt();
	Timer3.detachInterrupt();
	Timer1.stop();
	Timer3.stop();
	servo_1.attach(13);
	///*
	//中断技术可参考 http://arduino.cc/en/Reference/AttachInterrupt
	//LOW	当针脚输入为低时，触发中断
	//CHANGE	当针脚输入发生改变时，触发中断
	//RISING	当针脚输入由低变高时，触发中断
	//FALLING	当针脚输入由高变低时，触发中断
	//*/
	servo_1.write(72);
	Serial.begin(9600);
	Serial1.begin(9600);
	delay(1000);
	//rountine();
}

	
void loop() {

	switch (btOrder){
	case 0:					// 第一次发送，第二辆车启动
		MsTimer2::stop();
		Serial.begin(9600);
		Serial1.begin(9600);

		for (int i = 0; i < 20; i++)
		{
			writeBTData("ST");
		}
		btOrder = -1;
		delay(100);
		MsTimer2::set(1000, backToLine);
		//MsTimer2::set(1000, Stop);
		MsTimer2::start();
		break;

	case 1:
							// 第一辆车 到达交接区域，等待对方就位、对接
		readnum();			// 读取各颜色球的个数
		MsTimer2::stop();
		Serial.begin(9600);
		Serial1.begin(9600);
		Serial.println("case 1");
		while (readin != "S1")			// 第二辆车是否就位
		{
			readBTData();
			Serial.println("S1N");
			Serial.flush();
			delay(500);

		}

		servo_1.write(46);//++			// 打开第一个舵机，将一个颜色的球放出
		delay(2000);
		//Serial.println("STD_1");	
		while (readin != "S2")			// 第一次放球完毕，发送颜色、个数  等待对方回复指令
		{
			readBTData();
			writeBTData("S1DG" + String(numG));
			/*Serial1.println("S1D#");
			Serial1.flush();
			Serial.println("S1D");*/
		}

		servo_1.write(100);//+++			// 放出第二批球
		delay(2000);
		while (1)
		{
			writeBTData("S2D" + String(numO));		// 发送球的颜色个数
		}

		btOrder = -1;
		break;
	default:
		break;
	}
}
