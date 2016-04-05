#ifndef SERVEDRIVER_H
#define SERVEDRIVER_H


#include <iostream>
class ServoDriver{


public:
	ServoDriver();
    static void* execute(void * arguments);
  

private:


};

struct servo_controller_arg {
	ServoDriver* c;
	int movement;
};

#endif