#include "DistanceSensor.hpp"

DistanceSensor::DistanceSensor() {
    std::cout << "New DistanceSensor\n";
    /*
    this->fd = open("/sys/devices/ocp.3/helper.12/AIN1", O_RDONLY);
    //this->fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY);
    if (this->fd < 0) {
        std::cout << "error reading\n";
    }
    struct termios options;
    tcgetattr(this->fd, &options);
    //options.c_oflag = 0;
    cfsetispeed(&options, B9600);
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    //options.c_cflag &= ~PARENB;
    //options.c_cflag &= ~CSTOPB;
    //options.c_cflag &= ~CSIZE;
    //options.c_cc[VMIN]  = 1;
    //options.c_cc[VTIME] = 5;
    //options.c_cflag |= CS8;
    if (tcsetattr(this->fd, TCSANOW, &options) != 0) {
        std::cout << " from tcsetattr" << std::endl;
    }
    */


}

int DistanceSensor::getDistance()
{
    int n = 0;
    int spot = 0;
    char buf = '\0';

    /* Whole response*/
    char response[9];
    //memset(response, '\0', sizeof(response));
    printf("Hey hey\n");

    do {
        n = read(this->fd, &buf, 1);
        printf("buf: %c\n", buf);
        sprintf(&response[spot], "%c", buf );
        spot += n;
        printf("spot: %d\n", spot);
    } while( n > 0 && spot < 9);

    if (n < 0) {
        std::cout << "Error reading: " << strerror(errno) << std::endl;
    }
    else if (n == 0) {
        std::cout << "Read nothing!" << std::endl;
    }
    else {
        std::cout << "Response: " << response << std::endl;
    }

}

int DistanceSensor::getMoreDistance(){
       FILE *fp;
    char buffer[10];

    fp = popen("cat /sys/devices/ocp.3/helper.12/AIN1", "r");
    if (fp != NULL)
    {
        while (fgets(buffer, 10, fp) != NULL)
            //printf("%s", buffer);
        pclose(fp);
    }
    int i;
    sscanf(buffer, "%d", &i);

    double mv_inch = 767/512.0;
    float inch_distance = i/mv_inch;
    printf("Inch: %f\n", inch_distance);
    return inch_distance;
}



int main() {
    DistanceSensor ds = DistanceSensor();
    std::cout << "Constructed" << std::endl;
    while (true) {
        ds.getMoreDistance();
    }
}
