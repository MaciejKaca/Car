#include "sensorHandling.h"
#include "common.h"
#include <future>
#include <vector>
#include <wiringPi.h>
#include <math.h>
#include <iostream>
#include "RS-232/rs232.h"

struct SensorData
{
    int sensorNumber :3,
         measurment  :10;
};

SensorHandling::SensorHandling()
{
}

void SensorHandling::open_comport()
{
    const char mode[]={'8','N','1',0};

    if(RS232_OpenComport(cport_nr, bdrate, mode))
    {
        printf("Can not open comport\n");
    }
}

int SensorHandling::measurments[NUMBER_OF_SENSORS];

void SensorHandling::read_measurments()
{
    SensorData sensorData;
    while(true)
    {
        int n = RS232_PollComport(cport_nr, (unsigned char*)(&sensorData), sizeof(sensorData));
        if(n > 0)
        {
            //str_recv[n] = 0;   /* always put a "null" at the end of a string! */
            std::cout << "Sensor: " << sensorData.sensorNumber << std::endl;
            std::cout << "Measurment: " << sensorData.measurment << std::endl;
            measurments[sensorData.sensorNumber] = sensorData.measurment;
        }
        usleep(100);  /* sleep for 0.1 Second */
    }   
}

void SensorHandling::start_measuring()
{
    open_comport();
    usleep(2000000);
    auto result = std::async(std::launch::async, read_measurments);
}
