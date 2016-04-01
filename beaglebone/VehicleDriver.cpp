// my first program in C++
#include <pthread.h>
#include "MotorDriver.hpp"
#define MOVE_FORWARD = 1


int main()
{
  std::cout << "Hello World!" << "\n";
  bool running = true;
  int command = -1;
  MotorDriver* my_Controller = new MotorDriver();
  while(running){
  	std::cin >> command;
  	std::cout << "The value you entered is: " << command << "\n";
  	struct controller_arg my_args;
    my_args.c = my_Controller;
    my_args.movement = command;
    pthread_t thrd;
  	pthread_create(&thrd, NULL, &MotorDriver::execute, (void*)&my_args);
  	
  }
}