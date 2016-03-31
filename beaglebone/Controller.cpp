#include "Controller.hpp"

Controller::Controller(){
	std::cout << "New controller\n";
}

void* Controller::execute(void * arguments)
{
	std::cout << "Executing Command\n";
	struct controller_arg *args = (struct controller_arg *)arguments;
	return ((Controller *)args->c)->moveForward(args->movement);
}
void* Controller::moveForward(int movement)
{
	std::cout << "Moving forward " << movement << "\n";
}

