#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

void dcDrive(void)
{
	analogWrite(DCmotorPwm, DCSPEED);
	digitalWrite(DCmotorPin1, LOW);
	digitalWrite(DCmotorPin2, HIGH);
}
