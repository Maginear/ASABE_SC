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
	pinMode(motor_left_pin1, OUTPUT);
	pinMode(motor_left_pin2, OUTPUT);
	pinMode(motor_left_pin3, OUTPUT);
	pinMode(motor_left_pin4, OUTPUT);
	pinMode(motor_right_pin1, OUTPUT);
	pinMode(motor_right_pin2, OUTPUT);
	pinMode(motor_right_pin3, OUTPUT);
	pinMode(motor_right_pin4, OUTPUT);
	pinMode(sensor_1, INPUT);
	pinMode(sensor_2, INPUT);
	pinMode(sensor_3, INPUT);
	pinMode(sensor_4, INPUT);
	pinMode(sensor_5, INPUT);
	pinMode(sensor_6, INPUT);
	pinMode(sensor_7, INPUT);
	pinMode(sensor_8, INPUT);

	PID_inti();
	Timer1.initialize(Stepinterval);	// 设置步进电机的初始 节拍间隔
	Timer1.attachInterrupt(DriveLeft); // Drive Left Motor to run every stepinterval us	传入回调函数
	Timer3.initialize(Stepinterval);	// 同上
	Timer3.attachInterrupt(DriveRight);

	MsTimer2::set(ReadSensorInterval, updatePID); // 设置传感器扫描间隔， 以及回调函数
	MsTimer2::start();

	Serial.begin(9600);
}



void loop()
{
	// Test by ZZL. 2016/04/30, 01:24:22
}
