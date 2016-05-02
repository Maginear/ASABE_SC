/*
* ASABE 2016 ZJUer
* This part is used to read sensors data and adjust the motor
* Last Edit by Magy
* 2016/05/02
*
*/
#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

float ReadSensor()
{
	unsigned char state[sensor_num], num = 0, corner_status = 0;
	float sum = 0;
	float output = 0;

	for (int i = 0; i < sensor_num; ++i)
	{
		state[i] = digitalRead(sensor[i]);
		if (state[i] == HIGH && i < (sensor_num - 1) && i > 0)	// ֻ���м���������������������
		{
			sum += weight[i];
			num++;
		}
		//Serial.print("s:s:");
		//Serial.print(i);
		//Serial.println(state[i]);
	}

	//      Serial.println(state[i]);

	corner_status = state[7] << 4 + state[0];	// �����������˵㴫�����������ںϣ���Ϊת����ж�
	switch (corner_status)
	{
	case 0x11:
		corner = 3;	// ���߶��к��ģ�corner = 3;
		break;
	case 0x10:
		corner = 2;	// ������к��ߣ�corner = 1
		break;
	case 0x01:
		corner = 1;	// ���ұ��к��ߣ�corner = 2
		break;
	default:
		corner = 0;	// �������˴������޺��� corner = 0;
		break;
	}

	if (num != 0)
		output = sum / num;
	return output;
}


