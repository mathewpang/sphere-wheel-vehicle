#ifndef CON_H
#define CON_H

#include <iostream>
#include "Motor.hpp"
#include <string>
class MotorDriver
{
public:
  MotorDriver();
  static void* execute(void * arguments);
  void *moveForward(int movement);
  void* stop();
  int bar;
private:
	Motor* motor_zero;
	Motor* motor_one;
	Motor* motor_two;
};

struct controller_arg {
	MotorDriver* c;
	int movement;
};


#endif