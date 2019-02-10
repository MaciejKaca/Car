#pragma once
#include "common.h"

class SensorHandling
{
    public:
        SensorHandling();
        static float sensorMeasurments[NUMBER_OF_SENSORS];
        void start_measuring(float * const arr_ptr);
        
    private:
        static int triggerDelay;
        static int triggerPin;
        static void trigger_sensor();
        static void measure(float * const arr_ptr);
}; 