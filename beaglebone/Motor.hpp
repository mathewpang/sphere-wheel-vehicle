#ifndef MOTOR_H
#define MOTOR_H
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

#include <unistd.h>

class Motor
{
public:
	 Motor(int file_d, int motor_id);
	int setSpeed(int speed);
private:
    int file;
    int motor_id;
    uint8_t forward;
    uint8_t reverse;
//Qik 2s9v1
 
/*  The other motor controller
    const uint8_t MOTOR_SAFE_START = 0x83;
    const uint8_t MOTOR_FWD = 0x85;
    const uint8_t MOTOR_REV = 0x86;
    const uint8_t MOTOR_BRAKE = 0x92;
    const uint8_t MOTOR_GET_VAR = 0xA1;
    const uint8_t MOTOR_SET_LIMIT = 0xA2;
    const uint8_t MOTOR_STOP = 0xE0;
*/
};

#endif