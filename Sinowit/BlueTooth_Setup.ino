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
	digitalWrite(AT, HIGH); //AT�ĵ�ƽ���ߣ���������ATָ��
	Serial.begin(9600);//����Ӧ�ú����ģ��ͨ�Ų�����һ��
	delay(100);
	Serial.println("AT");
	delay(100);
	Serial.println("AT+NAME=Sinowit_Master");//����ģ����
	delay(100);
	Serial.println("AT+ROLE=1");//��������ģʽ��0�ӻ���1����
	delay(100);
	Serial.println("AT+PSWD=0000");//����������룬��1234
	delay(100);
	Serial.println("AT+UART=9600,0,0");//���ò�����9600��ֹͣλ1��У��λ��
	delay(100);
	Serial.println("AT+RMAAD");//�������б�
	delay(100);
	Serial.println("AT+BIND=0012,08,060146");//�趨�ӻ��ĵ�ַ�����ָ�ʽһ�¡�
	delay(100);
	Serial.println("AT+CMODE=0");//�����Զ�����
	delay(100);
}
void loop()
{
	digitalWrite(LED, HIGH);    /*ֻ����֤��������arduino�ɹ�������������ģ���޹�*/
	delay(500);
	digitalWrite(LED, LOW);
	delay(500);
}
