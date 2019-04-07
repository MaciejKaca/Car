#include <iostream>
#include <wiringPi.h>
#include "sensorHandling.h"
#include <stdlib.h>
#include <future>
#include <unistd.h>

int main(int argc, char *argv[])
{
	wiringPiSetup();

	SensorHandling::start_measuring();
	int(*measurment)[NUMBER_OF_SENSORS] = &SensorHandling::measurments;

	while (true)
	{
		system("clear");

		std::cout << "Sensor 1: " << measurment[LEFT] << " cm" << std::endl;
		std::cout << "Sensor 2: " << measurment[RIGHT] << " cm" << std::endl;
		usleep(100);
	}

	return 0;
}
