
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

Servo colorservo;
int g_count = 0;
int array1[3];
int array2[3];
int ballcolor = 0;
int g_flag = 0;
int time1 = 0;
int det;
int pos = 0;
int stopservo = 2;
bool whether = 0;

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

	TSC_Init();
	colorservo.attach(13);  // attaches the servo on pin 13 to the servo object
	//Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(18), TSC_Count, RISING);
	//delay(10);
	for (pos = 00; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		colorservo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(3);                       // waits 15ms for the servo to reach the position
	}

	PID_inti();
	Timer1.initialize(Stepinterval);	// 设置步进电机的初始 节拍间隔
	Timer1.attachInterrupt(DriveLeft); // Drive Left Motor to run every stepinterval us	传入回调函数
	Timer3.initialize(Stepinterval);	// 同上
	Timer3.attachInterrupt(DriveRight);
	
	MsTimer2::set(ReadSensorInterval, updatePID); // 设置传感器扫描间隔， 以及回调函数
	MsTimer2::start();

	attachInterrupt(0, TurnLeft, RISING);		// 使用0号中断触发左转， 实际对应数字引脚2 (D2) ，触发条件为出现上升沿
	attachInterrupt(1, TurnRight, RISING);		// 使用1号中断，实际对应数字引脚3 (D3), 出发条件为出现上升沿
	Timer1.detachInterrupt();
	Timer3.detachInterrupt();
	/*
	中断技术可参考 http://arduino.cc/en/Reference/AttachInterrupt
	LOW	当针脚输入为低时，触发中断
	CHANGE	当针脚输入发生改变时，触发中断
	RISING	当针脚输入由低变高时，触发中断
	FALLING	当针脚输入由高变低时，触发中断
	*/
	Serial.begin(9600);
	Serial1.begin(9600);
	//dcDrive();
	rountine();
	//Stop();

}

	
void loop() {
	// put your main code here, to run repeatedly:
	//switch (stopservo){
	//case 0:
	//	//color();
	//	backandforth();
	//	break;
	//case 1:
	//	if (!whether){
	//		colorin();
	//	}
	//	if (whether){
	//		color();
	//		//delay(1000);
	//	}
	//	break;
	//default:
	//	break;
	//}
	//
	//Serial.println(Serial1.read());
}
