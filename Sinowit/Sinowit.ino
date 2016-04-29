  /*
* MotorKnob
*
* A stepper motor follows the turns of a potentiometer
* (or other sensor) on analog input 0.
*
* http://www.arduino.cc/en/Reference/Stepper
* This example code is in the public domain.
*/
#include <Stepper.h>
#include <TimerOne.h>
#include <TimerThree.h>
#include <MsTimer2.h>

// change this to the number of steps on your motor
#define STEPS 400 //因为是8拍， 所以360 / 0.9
#define uchar unsigned char
#define uint unsigned int

#define PC 2  // 比例放大系数
#define IC 2    //积分放大系数
#define DC 6    //大系数

#define motor_left_pin1 22
#define motor_left_pin2 24
#define motor_left_pin3 26
#define motor_left_pin4 28

#define motor_right_pin1 30
#define motor_right_pin2 32
#define motor_right_pin3 34
#define motor_right_pin4 36

#define sensor_1 46
#define sensor_2 48
#define sensor_3 50
#define sensor_4 52

#define sensor_num 4


#define Basic_Left  50 //五步 后期会归到10步
#define Basic_Right 50 //
#define MAX 100
#define MIN 0


typedef struct p
{
float  error_1;//上次的误差
float sumerror;
} PID;
PID Pid;
PID *pid = &Pid;

uchar detection, sample = 0, corner = 0, k, flag;
int weight[] = {-8, -2, 2, 8}; //传感器的权值
int sensor[] = {46, 48, 50, 52};
int pidOut = 0;                 // pid的输出值

long Stepinterval = 4000;    //步进电机每个节拍之间的时间 4ms
long ReadSensorInterval = 10000;  //红外传感器的读取间隔时间

void PID_inti()//PID初始化
{
  pid->error_1 = 0;
  pid->sumerror = 0;
}


// 左右两端传感器无黑线 corner = 0;
// 最左边有黑线，corner = 1
// 最右边有黑线，corner = 2
// 两边都有黑心，corner = 3;
float ReadSensor()
{
  int state[sensor_num], num = 0;
  float sum = 0;
  float output = 0;

 for (int i = 0; i < sensor_num; ++i)
 {
   state[i] = digitalRead(sensor[i]);
 }
  // state[0] = digitalRead(sensor_1);
  // state[1] = digitalRead(sensor_2);
  // state[2] = digitalRead(sensor_3);
  // state[3] = digitalRead(sensor_4);

  for (int i = 0; i < sensor_num; i++)
    if (state[i] == LOW)
    {
//      Serial.print("s:s:");
//      Serial.println(i);
//      Serial.println(state[i]);
      if (i == 0)
      {
        corner = 1;
      }
      if (i == 3)
      {
        if (corner == 1)
        {
          corner = 3;
        }
        else
        {
          corner = 2;
        }
      }
      sum += weight[i];
      num++;
    }
  if (sum == 0)
    pid->sumerror = 0;
  if(num != 0)
    output = sum / num;
  return output;
}

int  PIDCal(float error)//PID计算。位置式。
{
  float output, derror;

  pid->sumerror += error;

  derror = (error - pid->error_1);

  output = error * PC + pid->sumerror * IC + derror * DC;

  pid->error_1 = error;
  return (int)(output + 0.5);
}

int right_step = 0;
int left_step = 0;
int leftOrRight = 0;

void DriveLeft(void)
{
  leftOrRight = 0;
  MotorStep();
}

void DriveRight(void)
{
  leftOrRight = 1;
  MotorStep();
}

void MotorStep()
{
  int Pin0, Pin1, Pin2, Pin3, thisStep = 0;
  if (leftOrRight)   //左边电机
  {
//    Pin0 = 22;
//    Pin1 = 24;
//    Pin2 = 26;
//    Pin3 = 28;
    Pin0 = 28;
    Pin1 = 26;
    Pin2 = 24;
    Pin3 = 22;
    thisStep = left_step;
  }
  else
  {
    Pin0 = 36;
    Pin1 = 34;
    Pin2 = 32;
    Pin3 = 30;
    thisStep = right_step;
  }

    switch(thisStep)
    {
      case 0:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);//32A
      break;
      case 1:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);//10B
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      break;
      case 2:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      break;
      case 3:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
      case 4:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      break;
      case 5:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      break;
      case 6:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      break;
      case 7:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
      default:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
    }
    thisStep++;

    if(thisStep>7)
    {
      thisStep=0;
    }


  if (leftOrRight)   //左边电机
  {
    left_step = thisStep;
  }
  else
  {
    right_step = thisStep;
  }
}

int steplimit(int stepnum)
{
  if (stepnum > MAX)
    stepnum = MAX;
  if (stepnum < MIN)
    stepnum = MIN;
  return stepnum;
}

void MotorAdjust(int pidOut)
{
  int l_step = Stepinterval;
  int r_step = Stepinterval;
  if (pidOut != 0)
  {
    l_step = Basic_Left - pidOut;
    r_step = Basic_Right + pidOut;
    l_step = steplimit(l_step);
    r_step = steplimit(r_step);
    int stepSum = l_step + r_step;
    l_step = l_step * 10 / stepSum;
    r_step = r_step * 10 / stepSum;
  }
  Timer1.setPeriod(l_step * 1000);  // 更新左侧电机的节拍时间间隔
  Timer3.setPeriod(r_step * 1000);
}

void setup()
{
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(46, INPUT);
  pinMode(48, INPUT);
  pinMode(50, INPUT);
  pinMode(52, INPUT);

  PID_inti();
  Timer1.initialize(Stepinterval);
  Timer1.attachInterrupt(DriveLeft); // Drive Left Motor to run every stepinterval us
  Timer3.initialize(Stepinterval);
  Timer3.attachInterrupt(DriveRight);
  MsTimer2::set(ReadSensorInterval, updatePID); // 500ms period
  MsTimer2::start();
  
  Serial.begin(9600);
}

void updatePID(void)
{
  float senVal = ReadSensor();
//  Serial.print("senVal:" );
//  Serial.println(senVal);
  pidOut = PIDCal(senVal);

  MotorAdjust(pidOut);
}

void loop()
{
	  // Test by Magy. 2016/04/30
}
