#include <MsTimer2.h>
#include <Servo.h>


#define LED    8  
#define S0     7   // Please notice the Pin's define 在上。
#define S1     6
#define S2     4
#define S3     5
#define OUT    3
#define numG_1  30
#define numG_2  32
#define numG_3  34  //串口引脚1、2、3
#define numO_1  36
#define numO_2  38
#define numO_3  40
#define dcpwm   11
//SoftwareSerial BT(8, 9);//R/T
Servo colorservo;

int g_count = 0;
int array1[3];
int array2[3];
int ballcolor = 0;
int g_flag = 0;
int time1 = 0;
int det;
int pos = 0;
bool stopservo = 1;
bool whether = 0;
bool messagesend = 0;
int avoid = 0;
int greater = 0;
char color2send;
int numOrange = 0;
int numGreen = 0;


void TSC_Init()
{
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(LED, OUTPUT);
	pinMode(numG_1, OUTPUT);
	pinMode(numG_2, OUTPUT);
	pinMode(numG_3, OUTPUT);
	pinMode(numO_1, OUTPUT);
	pinMode(numO_2, OUTPUT);
	pinMode(numO_3, OUTPUT);
	pinMode(dcpwm, OUTPUT);

	digitalWrite(S0, HIGH);  // OUTPUT FREQUENCY SCALING 20%
	digitalWrite(S1, LOW);
	digitalWrite(numG_1, LOW);
	digitalWrite(numG_2, LOW);
	digitalWrite(numG_3, LOW);
	digitalWrite(numO_1, LOW);
	digitalWrite(numO_2, LOW);
	digitalWrite(numO_3, LOW);
	
}
void TSC_FilterColor(int Level01, int Level02)
{
	if (Level01 != 0)
		Level01 = HIGH;

	if (Level02 != 0)
		Level02 = HIGH;

	digitalWrite(S2, Level01);
	digitalWrite(S3, Level02);
}
void TSC_WB(int Level0, int Level1)      //White Balance
{
	g_count = 0;
	g_flag++;
	TSC_FilterColor(Level0, Level1);
	MsTimer2::set(100, TSC_Callback);            // set 0.1s period
}
void TSC_Count()
{
	g_count++;
}
void colorin() 
{
	digitalWrite(LED, HIGH);
	delay(10);
	MsTimer2::set(100, TSC_Callback1);
	digitalWrite(S2, HIGH);
	digitalWrite(S3, HIGH);
	g_count = 0;
	MsTimer2::start();
	delay(105);
	if (det>100)
	{
		whether = 1;
		Serial.print("Start detect");
	}
	MsTimer2::stop();
	g_count = 0;
	digitalWrite(LED, LOW);
	if (avoid<10)
	{
		if (messagesend == 1) 
		{
			avoid += 1;
		}
	}
	else 
	{
		avoid = 0;
		messagesend = 0;
		greater = 0;
		//统计球的颜色
		if (color2send != 'G') 
		{
			numGreen += 1;
			//writeblue();
			color2send = '1';
			Serial.println(numGreen);
		}
		else if (color2send != 'O') 
		{
			numOrange += 1;
			color2send = '1';
			Serial.println(numOrange);
		}
		/*if (numGreen + numOrange == 1) {
			digitalWrite(Start, HIGH);
		}*/
	}
	//delay(2000);
}
void TSC_Callback1()
{
	//Serial.print("->Dectct G=");
	//Serial.println(g_count);
	det = g_count;
	g_count = 0;
}
void TSC_Callback()
{
	if (time1<3) 
	{
		switch (g_flag)
		{
		case 0:
			TSC_WB(LOW, LOW);              //Filter without Red
			for (int i = 0; i<2; i += 1) 
			{
				if (i == 0) 
				{
					int aa = array1[time1 - 1];
					Serial.print(aa);
					Serial.print(",");
				}
				else 
				{
					int bb = array2[time1 - 1];
					Serial.print(bb);
					Serial.println("]");
				}
			}
			Serial.println("->WB Start");
			break;
		case 1:
			Serial.print("->Frequency R=");
			Serial.println(g_count);
			array1[time1] = g_count;
			TSC_WB(HIGH, HIGH);            //Filter without Green
			break;
		case 2:
			Serial.print("->Frequency G=");
			Serial.println(g_count);
			array2[time1] = g_count;
			TSC_WB(HIGH, LOW);             //Filter clear
			g_count = 0;
			g_flag = 0;
			Serial.print("[");
			time1++;
			break;
		default:
			break;
		}
		// Serial.print(int(g_array[0] * g_SF[0]));    
	}
	else 
	{
		int aveR = (array1[0] + array1[1] + array1[2]) / 3;
		int aveG = (array2[0] + array2[1] + array2[2]) / 3;
		if (aveR>aveG && aveR>300) 
		{
			ballcolor = 1;
			stopservo = 0;
			Serial.println("Orange ball");
			color2send = 'O';
		}
		else if (aveR<aveG && aveG>300) 
		{             //Green ball
			ballcolor = 2;
			stopservo = 0;
			Serial.println("Green ball");
			color2send = 'G';
		}
		time1 = 0;
	}
}
void backandforth()
{
	while (stopservo != 1) 
	{
		switch (ballcolor)
		{
		case 1:
			for (pos = 60; pos <= 80 + greater * 5; pos += 1) 
			{ // goes from 0 degrees to 180 degrees
				colorservo.write(pos);              // tell servo to go to position in variable 'pos'
				delay(100);									//delay(1);                       // waits 15ms for the servo to reach the position
			}
			delay(500);
			for (pos = 80; pos >= 40; pos -= 1) 
			{ // goes from 180 degrees to 0 degrees
				colorservo.write(pos);              // tell servo to go to position in variable 'pos'
				delay(100);                       // waits 15ms for the servo to reach the position
			}
			stopservo = 1;
			break;
		case 2:
			for (pos = 60; pos >= 00; pos -= 1) 
			{
				colorservo.write(pos);
				delay(100);                       
			}
			delay(500);
			for (pos = 20; pos <= 50; pos += 1) 
			{ // goes from 0 degrees to 180 degrees
				colorservo.write(pos);              // tell servo to go to position in variable 'pos'
				delay(100);                       // waits 15ms for the servo to reach the position
			}
			stopservo = 1;
			break;
		default:
			delay(400);
			break;
		}
		messagesend = 1;
	}
	whether = 0;
	greater += 1;
	//stopservo = 0;
}
void color() 
{
	// put your setup code here, to run once:
	digitalWrite(LED, HIGH);
	delay(30);
	MsTimer2::set(100, TSC_Callback);
	MsTimer2::start();
	//attachInterrupt(digitalPinToInterrupt(18), TSC_Count, RISING);  
	//digitalWrite(S2, HIGH);
	delay(105);
	MsTimer2::stop();
}

void showNum(int numg, int numo)
{
	digitalWrite(numG_1, numg % 2);
	numg = (numg - numg % 2) / 2;
	digitalWrite(numG_2, numg % 2);
	numg = (numg - numg % 2) / 2;
	digitalWrite(numG_3, numg % 2);

	digitalWrite(numO_1, numo % 2);
	numo = (numo - numo % 2) / 2;
	digitalWrite(numO_2, numo % 2);
	numo = (numo - numo % 2) / 2;
	digitalWrite(numO_3, numo % 2);

	//if (a>3){
	//  digitalWrite(ct1, HIGH);
	//  a=a-4;
	//  }
	//if(a>1){
	//  digitalWrite(ct2, HIGH);
	//  a=a-2;
	//  }
	//if(a>0){
	//  digitalWrite(ct2, HIGH);
	//  }
}

void setup() 
{
	// put your setup code here, to run once:
	//color();
	TSC_Init();
	colorservo.attach(12);  // attaches the servo on pin 13 to the servo object
	Serial.begin(9600);
	//  BT.begin(9600);
	attachInterrupt(digitalPinToInterrupt(3), TSC_Count, RISING);
	delay(10);
	for (pos = 00; pos <= 50; pos += 1) 
	{ 
		// goes from 0 degrees to 180 degrees
										  // in steps of 1 degree
		colorservo.write(pos);              // tell servo to go to position in variable 'pos'
		delay(15);                       // waits 15ms for the servo to reach the position
	}
	pinMode(dcpwm, OUTPUT);
	analogWrite(dcpwm, 100);//直流调速
}

void loop() 
{
	// put your main code here, to run repeatedly:
	
	switch (stopservo) 
	{
	case 0:
		//color();
		backandforth();
		break;
	case 1:
		if (!whether) 
		{
			colorin();
		}
		if (whether) 
		{
			color();
			//delay(1000);
		}
		break;
	default:
		break;
	}
	
	showNum(numGreen, numOrange);
	//analogWrite(dcpwm, 100);//直流调速
	/*for (int i = 0; i < 255; i++)
	{
		analogWrite(dcpwm, i);
		delay(100);
	}
	for (int i = 255; i > 0; i--)
	{
		analogWrite(dcpwm, i);
		delay(100);
	}*/

}
