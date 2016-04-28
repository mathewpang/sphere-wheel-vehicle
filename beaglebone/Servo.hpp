#ifndef SERVO_H
#define SERVO_H
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>


class Servo
{
public:
     Servo(int file_d, int servo_channel, int offset);
    int setAngle(float angle);
    int getPosition();
private:
    int angleOffset;
    int file;
    int servo_channel;
    int pulseRange;
    int getPulseWidth(float angle);
    int setSpeedLimit(int speed);
    int setAccelLimit(int accel);
    int sendCommand(uint8_t com, int num);
};

#endif
