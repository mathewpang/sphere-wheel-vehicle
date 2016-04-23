#include "Motor.hpp"

const uint8_t MOTORM0FORWARD = 0x88;
const uint8_t MOTORM0REVERSE = 0x8A;
const uint8_t MOTORM1FORWARD = 0x8C;
const uint8_t MOTORM1REVERSE = 0x8E;

Motor::Motor(int file_d, int motor_id){
    this->file = file_d;
    this->motor_id = motor_id;
    if(motor_id == 0){
        this->forward = MOTORM0FORWARD;
        this->reverse = MOTORM0REVERSE;
    }
    else{
        this->forward = MOTORM1FORWARD;
        this->reverse = MOTORM1REVERSE;
    }
 }

int Motor::setSpeed(int speed) {
    //uint8_t command[] = {0xAA, 0x09, forward, speed};
    uint8_t command[] = {this->forward, speed};
    if(speed < 0){
         command[0] = this->reverse;
         command[0] = speed*-1;
    }
    std::cout << "Setting speed\n";
    if (write(file, command, sizeof(command)) == -1)  {
        std::cout << "Error writing.";
        return -1;
    }
    return speed;

}