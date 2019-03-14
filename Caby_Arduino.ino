#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor_center(8,9);
UltraSonicDistanceSensor distanceSensor_left(10,11);
UltraSonicDistanceSensor distanceSensor_right(12,13);
float cm,cm_center,cm_left,cm_right;      //保存障碍距离值
float temp1;

bool moto_status = false;

int in1=2;  //左侧电机
int in2=4;
int EA=3;

int in3=5;  //右侧电机
int in4=7;
int EB=6;


void forward(int speed_left, int speed_right) 
//函数调用时分别传送左右轮的速度参数过来，既能前进也能转向。
{
  /*小车前进模块*/
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(EA, speed_left);
  analogWrite(EB, speed_right+speed_right*0.08);
  moto_status = true;
}

void backward(int speed_left, int speed_right)
//函数调用时分别传送左右轮的速度参数过来，既能后退也能后退转向。
{
  /*小车后退模块*/
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EA, speed_left);
  analogWrite(EB, speed_right);
  moto_status = true;
}

void caby_Stop()
{
  /*小车停止模块*/
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(EA, HIGH);
  digitalWrite(EB, HIGH);
  moto_status = false;
}

void caby_Brake()
{
  /*小车制动模块*/
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(EA, LOW);
  digitalWrite(EB, LOW);
  moto_status = false;
}

void caby_turn()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(EA, HIGH);
  digitalWrite(EB, HIGH);
  moto_status = true;
}

void setup()
{
  Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EA, OUTPUT);
  pinMode(EB, OUTPUT);

}

void loop()
{
  Serial.print("center=");
  Serial.print(distanceSensor_center.measureDistanceCm());
  Serial.print("  left=");
  Serial.print(distanceSensor_left.measureDistanceCm());
  Serial.print("   right=");
  Serial.println(distanceSensor_right.measureDistanceCm());
  
  cm_center=distanceSensor_center.measureDistanceCm();
  if(cm_center<0)
    cm_center=30;
  cm_left=distanceSensor_left.measureDistanceCm();
   if(cm_left<0)
    cm_left=30;
  cm_right=distanceSensor_right.measureDistanceCm();
   if(cm_right<0)
    cm_right=30;
  if (cm_center < cm_left)
    cm = cm_center;
  else
    cm = cm_left;
  if (cm > cm_right)
    cm = cm_right;
  Serial.print("cm=");
  Serial.println(cm);
  if ((cm < 20)&&(moto_status))
  {
    backward(100,100);
    delay(500);
    caby_turn();
    delay(200); //大概原地转向80度
  }
  forward(100, 100);
}
