#include "Servo.hpp"

const uint8_t SETTARGET = 0x84;
const uint8_t SETSPEEDLIMIT = 0x87;
const uint8_t SETACCELLIMIT = 0x89;
const uint8_t GETPOSITION = 0x90;
const float NEUTRALPULSE = 1500;
const float SERVORANGE = 90;
const float PULSERANGE = 900;
const float CONVERTTOQTRUSEC = 4;

Servo::Servo(int file_d, int servo_channel, int offset) {
    this->file = file_d;
    this->servo_channel = servo_channel;
    this->angleOffset = offset;
    setSpeedLimit(0);
    setAccelLimit(0);
}


int Servo::setAngle(float angle) {
    float targetAngle = angle;
    int target = getPulseWidth(targetAngle);
    std::cout << "Setting angle to " << targetAngle << " pulse " << target << "\n";
    return sendCommand(SETTARGET, target);
}

int Servo::getPulseWidth(float angle) {
    //Pulse width is returned in quarter microseconds.
    //Angle should be in degrees.
    return (int)(NEUTRALPULSE + (angle / SERVORANGE) * PULSERANGE) * CONVERTTOQTRUSEC;
}

int Servo::getPosition() {
    uint8_t command[] = {GETPOSITION, this->servo_channel};
    if (write(this->file, command, sizeof(command)) == -1)  {
        std::cout << "Error writing.";
        return -1;
    }
}


int Servo::setSpeedLimit(int speed) {
    return sendCommand(SETSPEEDLIMIT, speed);
}

int Servo::setAccelLimit(int accel) {
    return sendCommand(SETACCELLIMIT, accel);
}

int Servo::sendCommand(uint8_t com, int num) {
    uint8_t numLower7 = num & 0x7F;
    uint8_t numHigher7 = (num >> 7) & 0x7F;
    uint8_t command[] = {com, this->servo_channel, numLower7, numHigher7};
    if (write(this->file, command, sizeof(command)) == -1)  {
        std::cout << "Error writing.";
        return -1;
    }
    return num;
}
