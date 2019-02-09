#include <iostream>
#include <wiringPi.h>
#include "sensorHandling.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SensorHandling sensors;

    wiringPiSetup();
    sensors.start_measuring();

    while(true)
    {
        system("clear");
        
        std::cout << "Sensor 1: " << sensors.sensorMeasurments[0] << " cm" << std::endl;
        std::cout << "Sensor 2: " << sensors.sensorMeasurments[1] << " cm" << std::endl;
        delay(10);
    }

    return 0;
}