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

	//PID_inti();
	//Timer1.initialize(Stepinterval);	// 设置步进电机的初始 节拍间隔
	//Timer1.attachInterrupt(DriveLeft); // Drive Left Motor to run every stepinterval us	传入回调函数
	//Timer3.initialize(Stepinterval);	// 同上
	//Timer3.attachInterrupt(DriveRight);
	//
	MsTimer2::set(ReadSensorInterval, updatePID); // 设置传感器扫描间隔， 以及回调函数
	MsTimer2::start();

	Serial.begin(9600);
}

void loop()
{
	// Test by ZZL. 2016/04/30, 01:24:22
	// Test by MZH. 2016/05/02, 16:17
	/*ReadSensor();*/
}
