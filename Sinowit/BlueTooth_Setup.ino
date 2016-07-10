#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>
#include <SoftwareSerial.h>

#define AT 2
#define LED 13
void setup()
{
	pinMode(LED, OUTPUT);
	pinMode(AT, OUTPUT);
	digitalWrite(AT, HIGH); //AT的电平给高，用于输入AT指令
	Serial.begin(9600);//这里应该和你的模块通信波特率一致
	delay(100);
	Serial.println("AT");
	delay(100);
	Serial.println("AT+NAME=Sinowit_Master");//命名模块名
	delay(100);
	Serial.println("AT+ROLE=1");//设置主从模式：0从机，1主机
	delay(100);
	Serial.println("AT+PSWD=0000");//设置配对密码，如1234
	delay(100);
	Serial.println("AT+UART=9600,0,0");//设置波特率9600，停止位1，校验位无
	delay(100);
	Serial.println("AT+RMAAD");//清空配对列表
	delay(100);
	Serial.println("AT+BIND=0012,08,060146");//设定从机的地址，保持格式一致。
	delay(100);
	Serial.println("AT+CMODE=0");//开启自动连接
	delay(100);
}
void loop()
{
	digitalWrite(LED, HIGH);    /*只用于证明程序导入arduino成功，和设置蓝牙模块无关*/
	delay(500);
	digitalWrite(LED, LOW);
	delay(500);
}
