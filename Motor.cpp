#include"def.h"
#include"Motor.h"

#define MaxValue 1850

#include <Servo.h>

Motor::Motor()
{
    //目前最优1.2,0.35,0.35
    Pitch_PID.setPID(1.25,0.35,0.30);
    Roll_PID.setPID(1.25,0.35,0.30);
    Yaw_PID.setPID(1.0,0.02,0);

    Pitch_Offset = Roll_Offset = Yaw_Offset = Throttle = 0;
    Front = Back = Left = Right = 0;
    MinValue = 1092;
}

//根据传感器数据和遥控器信号计算四个电机的输出
void Motor::CalculateOutput(float yawRate,float pitchAngle,float rollAngle,Receiver MyReceiver)
{
    Throttle = MyReceiver.RxThr;

    Pitch_Offset = Pitch_PID.Calculate(-MyReceiver.RxEle/8,pitchAngle);
    Roll_Offset = Roll_PID.Calculate(MyReceiver.RxAil/8,rollAngle);
    Yaw_Offset = Yaw_PID.Calculate(-MyReceiver.RxRud/8,yawRate);

    if(Throttle<1200)
        Yaw_Offset = 0;
    if(abs(Yaw_Offset)>150)
    {
        if(Yaw_Offset>0)
            Yaw_Offset = 150;
        else
            Yaw_Offset = -150;
    }

    // 十字模式
	//       Front
	//   Left + Right
	//       Back
    Front = MotorLimitValue(Throttle + Pitch_Offset + Yaw_Offset);
    Right = MotorLimitValue(Throttle - Roll_Offset - Yaw_Offset);
    Left = MotorLimitValue(Throttle + Roll_Offset - Yaw_Offset);
    Back = MotorLimitValue(Throttle - Pitch_Offset + Yaw_Offset);
}

//信号限幅
float Motor::MotorLimitValue(int v)
{
 	if(v>MaxValue)
        return MaxValue;
	if(v<MinValue)
        return MinValue;
	return v;
}

void Motor::Lock()
{
    Front = Back = Left = Right = MinValue;
    OutPut();
}

void Motor::unLock()
{
    Pitch_PID.resetITerm();
    Roll_PID.resetITerm();
    Yaw_PID.resetITerm();
}
void Motor::OutPut()
{
  esc0.writeMicroseconds(Front);
  esc1.writeMicroseconds(Back);
  esc2.writeMicroseconds(Right);
  esc3.writeMicroseconds(Left);
}

void Motor::CalibrateESCs()
{
//Attach pins for ESCs (sets motor orientation)
#if defined(Mega2560)
  esc0.attach(4); //ESC 0 - Pin 11
  esc1.attach(3); //ESC 1 - Pin 10
  esc2.attach(5); //ESC 2 - Pin 13
  esc3.attach(6); //ESC 3 - Pin 12
#elif defined(Promini)
  esc0.attach(3); //ESC 0 - Pin 11
  esc1.attach(9); //ESC 1 - Pin 10
  esc2.attach(10); //ESC 2 - Pin 13
  esc3.attach(11); //ESC 3 - Pin 12
#endif // defined

  esc0.writeMicroseconds(1860);
  esc1.writeMicroseconds(1860);
  esc2.writeMicroseconds(1860);
  esc3.writeMicroseconds(1860);
  delay(3000); //Wait for 3 sec
  //Set lowest values
  esc0.writeMicroseconds(MinValue);
  esc1.writeMicroseconds(MinValue);
  esc2.writeMicroseconds(MinValue);
  esc3.writeMicroseconds(MinValue);
  delay(2000);
}
