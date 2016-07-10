#include "Sinowit.h"

void readBTData(void)
{
	if (Serial1.available())
	{
		readin =  Serial1.readStringUntil('#');
		Serial.println(readin);
		Serial.flush();
	}
}

void writeBTData(String str)
{
	Serial1.print(str);
	Serial1.print('#');
	Serial1.flush();
	delay(100);
}