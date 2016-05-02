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
		if (state[i] == LOW && i < (sensor_num - 1) && i > 0)	// 只将中间六个传感器用来做调整
		{
			sum += weight[i];
			num++;
		}
	}
	//      Serial.print("s:s:");
	//      Serial.println(i);
	//      Serial.println(state[i]);

	corner_status = state[7] << 4 + state[0];	// 将左右两个端点传感器的数据融合，作为转弯的判断
	switch (corner_status)
	{
	case 0x11:
		corner = 3;	// 两边都有黑心，corner = 3;
		break;
	case 0x10:
		corner = 2;	// 最左边有黑线，corner = 1
		break;
	case 0x01:
		corner = 1;	// 最右边有黑线，corner = 2
		break;
	default:
		corner = 0;	// 左右两端传感器无黑线 corner = 0;
		break;
	}

	if (sum == 0)
		pid->sumerror = 0;
	if (num != 0)
		output = sum / num;
	return output;
}


