#ifndef SERVOCON_H
#define SERVOCON_H

#include <iostream>
#include "Servo.hpp"
#include <string>
class ServoDriver
{
public:
    ServoDriver();
    int manual(float angle0, float angle1, float angle2);
private:
    Servo* servo_zero;
    Servo* servo_one;
    Servo* servo_two;


};


#endif
