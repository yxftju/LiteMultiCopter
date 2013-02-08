#include"SerialCom.h"

SerialCom::SerialCom()
{

}

void SerialCom::Init()
{
    //初始化串口通信，波特率
    Serial.begin(9600);
}

void SerialCom::SensorDataToPC(MPU6050 Sensor)
{
    Serial.println(F(""));
    Serial.println(F("MPU-6050"));

    Serial.print(F("accel x,y,z: "));
    Serial.print(Sensor.ReadAccX(), 3);
    Serial.print(F(", "));
    Serial.print(Sensor.ReadAccY(), 3);
    Serial.print(F(", "));
    Serial.print(Sensor.ReadAccZ(), 3);
    Serial.println(F(""));

    Serial.print(F("temperature: "));
    double dT = Sensor.ReadTemperature();
    Serial.print(dT, 3);
    Serial.print(F(" degrees Celsius"));
    Serial.println(F(""));

    Serial.print(F("gyro x,y,z : "));
    Serial.print(Sensor.ReadGyroX(), 3);
    Serial.print(F(", "));
    Serial.print(Sensor.ReadGyroY(), 3);
    Serial.print(F(", "));
    Serial.print(Sensor.ReadGyroZ(), 3);
    Serial.print(F(", "));
    Serial.println(F(""));
}
