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
    int soundSpeed = 340;
    int firstEchoPin = 4;
    int sensorEchoPin = firstEchoPin + sensorNumber;
    auto pulseStart = std::chrono::system_clock::now();
    auto pulseEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> pulseDuration;

    while(digitalRead(sensorEchoPin)==LOW)
       pulseStart = std::chrono::high_resolution_clock::now();
    while(digitalRead(sensorEchoPin)==HIGH)
       pulseEnd = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<float, std::micro> elapsedTime = pulseEnd - pulseStart;
    float toSeconds = (elapsedTime.count()/2)/1000000;
    float distance = soundSpeed * toSeconds;
    float distaceToCm = distance * 100;
    return distaceToCm;
}

void SensorHandling::trigger_sensor()
{
    digitalWrite(triggerPin, HIGH);
    delay(1);
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
            *measurment = results.get();
            measurment++;
        }

        sensorReading.clear();
    }
}
