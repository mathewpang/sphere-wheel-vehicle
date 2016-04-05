
#include "ServoDriver.hpp"

ServoDriver::ServoDriver(){

}

void* ServoDriver::execute(void * arguments)
{
  std::cout << "Executing Servo Command\n";
  struct servo_controller_arg *args = (struct servo_controller_arg *)arguments;
  
}