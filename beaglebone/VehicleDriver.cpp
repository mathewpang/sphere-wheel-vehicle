#include <pthread.h>
#include "MotorDriver.hpp"
#include "ServoDriver.hpp"
#define MOVE_FORWARD = 1

const float SERVO0_OFFSET = 0;
const float SERVO1_OFFSET = 0;
const float SERVO2_OFFSET = -0;
const float gear_ratio = 2.0;

float convert_angle(int servo_id, float angle, bool &isReversed){
    if(servo_id > 2 || servo_id < 0){
        return -1; //UNDEFINED ERROR
    }
    float converted = angle;

    if(servo_id == 0){
        converted += SERVO0_OFFSET;
    }
    if(servo_id == 1){
        converted += SERVO1_OFFSET;
    }
    if(servo_id == 2){
        converted += SERVO2_OFFSET;
    }
    while(converted > 90){
        converted -= 180;
        isReversed = !isReversed;
    }
    while(converted < -90){
        converted += 180;
        isReversed = !isReversed;
    }
    std::cout << "Servo id is: " << servo_id << " and angle is: " << converted << "\n";
    converted = converted/gear_ratio;
    return converted;
}

int main()
{
    std::cout << "Hello World!" << "\n";
    bool running = true;
    int command = -1;
    MotorDriver* my_Controller = new MotorDriver();
    ServoDriver* servo_controller = new ServoDriver();
    while(running){
        std::cin >> command;
        std::cout << "The value you entered is: " << command << "\n";
        //struct controller_arg my_args;
        //my_args.c = my_Controller;
        //my_args.movement = command;
        //pthread_t thrd;
        //pthread_create(&thrd, NULL, &MotorDriver::execute, (void*)&my_args);
        bool isReversed0 = false;
        bool isReversed1 = false;
        bool isReversed2 = false;
        float serv_0 = convert_angle(0, command, isReversed0);
        float serv_1 = convert_angle(1, command, isReversed1);
        float serv_2 = convert_angle(2, command, isReversed2);

        servo_controller->manual(serv_0, serv_1, serv_2);
    }
}
