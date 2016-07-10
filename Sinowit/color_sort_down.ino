#include <MsTimer2.h>
#include <Servo.h>
#include "Sinowit.h"
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>

#define LED    12  
#define S0     8   // Please notice the Pin's define 在上。
#define S1     9
#define S2     10
#define S3     11
#define OUT    18





void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(LED, OUTPUT);
  //pinMode(OUT, INPUT);
  
  digitalWrite(S0, HIGH);  // OUTPUT FREQUENCY SCALING 20%
  digitalWrite(S1, LOW);  
}
void TSC_FilterColor(int Level01, int Level02)
{
  if(Level01 != 0)
    Level01 = HIGH;
  
  if(Level02 != 0)
    Level02 = HIGH;
  
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
void TSC_WB(int Level0, int Level1)      //White Balance
{
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  
  MsTimer2::set(100,TSC_Callback);            // set 0.1s period
}
void TSC_Count()
{
  g_count ++ ;
}
void colorin(){
  digitalWrite(LED, HIGH);
  delay(30);

  MsTimer2::set(100,TSC_Callback1); 
  digitalWrite(S2, HIGH); 
  digitalWrite(S3, HIGH);
  g_count=0;
  MsTimer2::start();
  delay(105);
  if (det>100){
  whether = 1;
  Serial.print("Start detect"); 
  }
  MsTimer2::stop();
  g_count = 0;
  digitalWrite(LED, LOW);
  MsTimer2::set(ReadSensorInterval, updatePID); // 设置传感器扫描间隔， 以及回调函数
  MsTimer2::start();
  //delay(2000);
}
void TSC_Callback1()
{
Serial.print("->Dectct G=");
Serial.println(g_count);
det=g_count;
g_count=0;
}
void TSC_Callback()
{
  if (time1<3){
  switch(g_flag)
  {
    case 0: 
         TSC_WB(LOW, LOW);              //Filter without Red
      for (int i = 0; i<2; i+=1){
      if(i== 0){
       int aa = array1[time1-1];
       Serial.print(aa);
       Serial.print(",");}
       else{
        int bb = array2[time1-1];
        Serial.print(bb);
       Serial.println("]");
      }}
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
  else{
   int aveR=(array1[0]+array1[1]+array1[2])/3;
   int aveG=(array2[0]+array2[1]+array2[2])/3;
    if(aveR>aveG && aveR>300){
      ballcolor=1;
      stopservo=0;
      Serial.println("Orange ball");
      }else if(aveR<aveG && aveG>300){             //Green ball
      ballcolor=2;
      stopservo=0;
      Serial.println("Green ball");
        }
    time1=0;    
    }
}
void backandforth()
{
  while (stopservo != 1){
  switch (ballcolor)
  {
  case 1:
    for (pos = 60; pos <= 80; pos += 1) { // goes from 0 degrees to 180 degrees
      colorservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(3);                       // waits 15ms for the servo to reach the position
    }
    delay(500);
    for (pos = 80; pos >= 40; pos -= 1) { // goes from 180 degrees to 0 degrees
      colorservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(3);                       // waits 15ms for the servo to reach the position
    }
    stopservo = 1;
    break;
  case 2:
    for (pos = 60; pos >= 00; pos -= 1) { 
      colorservo.write(pos);             
      delay(2);                       
    }
      delay(500);
    for (pos = 20; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
      colorservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(2);                       // waits 15ms for the servo to reach the position
    }
    stopservo = 1;
    break;
  default:
    delay(400);
    break;
  }}
  whether=0;
  //stopservo = 0;
}
void color() {
  // put your setup code here, to run once:
 digitalWrite(LED, HIGH);
 delay(30);
  MsTimer2::set(100,TSC_Callback); 
  MsTimer2::start();
  //attachInterrupt(digitalPinToInterrupt(18), TSC_Count, RISING);  
  //digitalWrite(S2, HIGH);
   delay(105);
  MsTimer2::stop(); 
}

void color_sort()
{
	stopservo = 1;
}