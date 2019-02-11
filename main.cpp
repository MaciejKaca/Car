#include <iostream>
#include <wiringPi.h>
#include "sensorHandling.h"
#include <stdlib.h>
#include <future>

float SensorHandling::sensorMeasurments[NUMBER_OF_SENSORS];

int main(int argc, char *argv[])
{
    wiringPiSetup();

    auto result = std::async(std::launch::async, SensorHandling::measure, SensorHandling::sensorMeasurments);

    while(true)
    {
        system("clear");
        
        std::cout << "Sensor 1: " << SensorHandling::sensorMeasurments[LEFT] << " cm" << std::endl;
        std::cout << "Sensor 2: " << SensorHandling::sensorMeasurments[RIGHT] << " cm" << std::endl;
        delay(10);
    }

    return 0;
}
