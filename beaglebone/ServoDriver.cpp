#include "ServoDriver.hpp"

const float servo_min_value = -90.0;
const float servo_max_value = 90.0;

ServoDriver::ServoDriver() {
    std::cout << "New Servo controller\n";
    int file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (file == -1) {
        std::cout << "Error opening file.\n";
    }
    struct termios options;
    tcgetattr(file, &options);
    cfsetispeed(&options, B38400);
    cfsetospeed(&options, B38400);
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcsetattr(file, TCSANOW, &options);

    uint8_t command[] = {0xAA};
    if (write(file, command, sizeof(command)) == -1)  {
        std::cout << "Error writing.";
    }

    servo_zero = new Servo(file, 0, 0);
    servo_one  = new Servo(file, 1, 0);
    servo_two  = new Servo(file, 2, 0);
}

int ServoDriver::manual(float angle0, float angle1, float angle2) {
    angle0 = std::min(servo_max_value, std::max(servo_min_value, angle0));
    angle1 = std::min(servo_max_value, std::max(servo_min_value, angle1));
    angle2 = std::min(servo_max_value, std::max(servo_min_value, angle2));
    std::cout << "Setting angle: \n";
    servo_zero->setAngle(angle0);
    servo_one->setAngle(angle1);
    servo_two->setAngle(angle2);
}
