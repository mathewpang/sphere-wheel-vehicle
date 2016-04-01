#include "MotorDriver.hpp"



MotorDriver::MotorDriver(){
  std::cout << "New Motor controller\n";
  int file_one = open("/dev/ttyO1", O_RDWR | O_NOCTTY);
    if (file_one == -1) {
        std::cout << "Error opening file.\n";
    }
  int file_two = open("/dev/ttyO2", O_RDWR | O_NOCTTY);
    if (file_two == -1) {
        std::cout << "Error opening file.\n";
    }
  struct termios options;
  tcgetattr(file_one, &options);
  cfsetispeed(&options, B38400);
  cfsetospeed(&options, B38400);
  options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
  options.c_oflag &= ~(ONLCR | OCRNL);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

  tcsetattr(file_one, TCSANOW, &options);
  tcsetattr(file_two, TCSANOW, &options);

  uint8_t command[] = {0xAA};
  if (write(file_one, command, sizeof(command)) == -1)  {
      std::cout << "Error writing.";
  }
  if (write(file_two, command, sizeof(command)) == -1)  {
      std::cout << "Error writing.";
  }


  motor_zero = new Motor(file_one, 0);
  motor_one = new Motor(file_one, 1);
  motor_two = new Motor(file_two, 0);

}

void* MotorDriver::execute(void * arguments)
{
  std::cout << "Executing Command\n";
  struct controller_arg *args = (struct controller_arg *)arguments;
  if(args->movement == 1){
   ((MotorDriver *)args->c)->moveForward(args->movement); 
  }
  else if(args->movement == 0){
    ((MotorDriver *)args->c)->stop();
  }
}

void* MotorDriver::moveForward(int movement)
{
  std::cout << "Moving forward " << movement << "\n";
  motor_zero->setSpeed(0x7F);
}

void* MotorDriver::stop()
{
  std::cout << "Stopping " << "\n";
  motor_zero->setSpeed(0x00);
}