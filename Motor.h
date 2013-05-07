#ifndef MOTOR_H
#define MOTOR_H

#include"Receiver.h"
#include"MPU6050.h"
#include"PID.h"

#include <Servo.h>

class Motor
{
    public:
        Motor();
        void CalculateOutput(MPU6050  MySensor,Receiver MyReceiver);
        float MotorLimitValue(int v);
        void Lock();
        void OutPut();
        void CalibrateESCs();

    public:
        int Throttle,Pitch_Offset,Roll_Offset,Yaw_Offset;//油门、副翼、升降舵、方向舵。(操纵时的附加到电机的偏量)
        int Front,Back,Left,Right;//四个电机的输出
        Servo esc0; //Pin 10
        Servo esc1; //Pin 11
        Servo esc2; //Pin 12
        Servo esc3; //Pin 13
};

#endif // MOTOR_H
