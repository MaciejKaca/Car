#pragma once
#include "common.h"

class SensorHandling
{
    public:
        SensorHandling();
        static void start_measuring();
        static int measurments[NUMBER_OF_SENSORS];
    private:
        static const int cport_nr = 24; /* /dev/ttyUSB0 */
        static const int bdrate = 9600;
        static void read_measurments();
        static void open_comport();
}; 