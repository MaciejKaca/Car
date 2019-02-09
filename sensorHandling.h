#pragma once
#include "common.h"

class SensorHandling
{
    public:
        SensorHandling();
        float sensorMeasurments[NUMBER_OF_SENSORS];
        void start_measuring();
        
    private:
        static int triggerDelay;
        static int triggerPin;
        static int firstEchoPin;
        void read_sensor(int sensorSide);
        void trigger_sensor();
        void measure();
};