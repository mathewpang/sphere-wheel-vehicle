#ifndef A_H
#define A_H

#include <iostream>
class Controller
{
public:
  Controller();
  static void* execute(void * arguments);
  void *moveForward(int movement);
  int bar;
};

struct controller_arg {
	Controller* c;
	int movement;
};


#endif