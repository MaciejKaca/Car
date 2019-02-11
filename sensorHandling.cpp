#include "sensorHandling.h"
#include "common.h"
#include <future>
#include <vector>
#include <wiringPi.h>
#include <math.h>
#include <iostream>

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

float get_sensor_measurment(int sensorNumber)
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
    return distance;
}

void SensorHandling::trigger_sensor()
{
    digitalWrite(triggerPin, HIGH);
    delay(10);
    digitalWrite(triggerPin, LOW);
}

void SensorHandling::measure(float * measurment)
{
    std::vector<std::future<float>> sensorReading;
    float * originalMeasurmentPtr = measurment;

    while(true)
    {
        delay(triggerDelay);

        trigger_sensor();

        for(int sensorNumber = 0; sensorNumber < NUMBER_OF_SENSORS; sensorNumber++)
        {
            sensorReading.push_back(std::async(std::launch::async, get_sensor_measurment, sensorNumber));
        }

        measurment = originalMeasurmentPtr;

        for(auto& results : sensorReading)
        {
            measurment++;
            *measurment = results.get();
        }

        sensorReading.clear();
    }
}