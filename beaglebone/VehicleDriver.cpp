#include <pthread.h>
#include <string>
#include <cstdlib>
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
    std::string command;
    MotorDriver* my_Controller = new MotorDriver();
    ServoDriver* servo_controller = new ServoDriver();
 
    while(running){
        std::cin >> command;
        std::string s = command;
        std::string d = "=";
        std::string token = s.substr(0, s.find(d));

        std::cout <<token << std::endl;

        std::string value_str = s.substr(s.find(d)+1, s.length());
        //std::string::size_type sz;   // alias of size_t hahahhaa
        int value_int = std::atoi (value_str.c_str());

        std::cout <<value_str << std::endl;   

        if (token.compare("Radius") == 0){
            struct controller_arg my_args;
            my_args.c = my_Controller;
            my_args.movement = value_int;
            pthread_t thrd;
            pthread_create(&thrd, NULL, &MotorDriver::execute, (void*)&my_args);

        } else if (token.compare("Angle") == 0){
            bool isReversed0 = false;
            bool isReversed1 = false;
            bool isReversed2 = false;
            float serv_0 = convert_angle(0, value_int, isReversed0);
            float serv_1 = convert_angle(1, value_int, isReversed1);
            float serv_2 = convert_angle(2, value_int, isReversed2);

            servo_controller->manual(serv_0, serv_1, serv_2);
        }    
    }
}
