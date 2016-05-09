/*
* ASABE 2016 ZJUer
* This part is used to read SENSORs data and adjust the motor
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
	unsigned char state[SENSOR_NUM], num = 0;
	float sum = 0;
	float output = 0;

	for (int i = 0; i < SENSOR_NUM; ++i)
	{
		state[i] = digitalRead(SENSOR[i]);
		if (state[i] == HIGH && i < (SENSOR_NUM - 1) && i > 0)	// 只将中间六个传感器用来做调整
		{
			sum += weight[i];
			num++;
		}
		//Serial.print("s:s:");
		//Serial.print(i);
		//Serial.println(state[i]);
	}

	//      Serial.println(state[i]);

	corner = state[7] << 4 + state[0];	// 将左右两个端点传感器的数据融合，作为转弯的判断
	

	if (num != 0)
		output = sum / num;
	return output;
}


