#include "sensorHandling.h"
#include "common.h"
#include <future>
#include <vector>
#include <wiringPi.h>
#include <math.h>

int SensorHandling::firstEchoPin = 5;
int SensorHandling::triggerDelay = 100;
int SensorHandling::triggerPin = 4;

SensorHandling::SensorHandling()
{
    pinMode(triggerPin, OUTPUT);
    for(int i=0; i < NUMBER_OF_SENSORS; i++)
    {
        pinMode(firstEchoPin+i,INPUT);
    }


    digitalWrite(triggerPin, LOW);
}

void SensorHandling::read_sensor(int sensorSide)
{
    int echoPin = sensorSide + firstEchoPin;
    auto pulseStart = std::chrono::system_clock::now();
    auto pulseEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> pulseDuration;
    float distance;


    while(digitalRead(echoPin)==LOW)
        pulseStart = std::chrono::system_clock::now();
    while(digitalRead(echoPin)==HIGH)
        pulseStart = std::chrono::system_clock::now();
    
    pulseDuration = pulseStart - pulseEnd;
    distance = roundf((17150 * pulseDuration.count()*100)/100);
}

void SensorHandling::trigger_sensor()
{
    while(true)
    {
        digitalWrite(triggerPin, HIGH);
        delay(1);
        digitalWrite(triggerPin, LOW);
    }
}

void SensorHandling::measure()
{
    std::vector<std::thread> sensorReading;

    for(int i = 0; i < 2; ++i)
    {
        sensorReading.push_back(std::thread(read_sensor, i));
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

void SensorHandling::start_measuring()
{
    std::async(&measure);
}