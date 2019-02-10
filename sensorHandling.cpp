#include "sensorHandling.h"
#include "common.h"
#include <future>
#include <vector>
#include <wiringPi.h>
#include <math.h>

int SensorHandling::triggerDelay = 100;
int SensorHandling::triggerPin = 1;

SensorHandling::SensorHandling()
{
    const int firstEchoPin = 4;
    pinMode(triggerPin, OUTPUT);
    for(int i=firstEchoPin; i < NUMBER_OF_SENSORS; i++)
    {
        pinMode(firstEchoPin+i,INPUT);
    }


    digitalWrite(triggerPin, LOW);
}

void getSensorMeasurment(int sensorNumber, float *measurment)
{
    int firstEchoPin = 4;
    int sensorEchoPin = firstEchoPin + sensorNumber;
    auto pulseStart = std::chrono::system_clock::now();
    auto pulseEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> pulseDuration;
    float distance;

    while(digitalRead(sensorEchoPin)==LOW)
        pulseStart = std::chrono::system_clock::now();
    while(digitalRead(sensorEchoPin)==HIGH)
        pulseStart = std::chrono::system_clock::now();
    
    pulseDuration = pulseStart - pulseEnd;
    distance = roundf((17150 * pulseDuration.count()*100)/100);
    *measurment = distance;
}

void SensorHandling::trigger_sensor()
{
    digitalWrite(triggerPin, HIGH);
    delay(1);
    digitalWrite(triggerPin, LOW);
}

void SensorHandling::measure(float * const arr_ptr)
{
    std::vector<std::thread> sensorReading;

    for(int sensorNumber = 0; sensorNumber < 2; ++sensorNumber)
    {
        sensorReading.push_back(std::thread(getSensorMeasurment, sensorNumber, arr_ptr+sensorNumber ));
    }

    while(true)
    {
        delay(triggerDelay);

        trigger_sensor();

        for(auto& thread : sensorReading)
        {
            thread.join();
        }
    }
}

void SensorHandling::start_measuring(float * const arr_ptr)
{
    std::async(&measure, arr_ptr);
}