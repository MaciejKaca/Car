#define NUMBER_OF_SENSORS 2

const int triggerPin = 2;
const int firstEchoPin = 3;
const int lastEchoPin = (firstEchoPin+NUMBER_OF_SENSORS)-1;
const int delayBetweenMeasurments = 10;
const int triggerDuration = 10;
const float soundSpeed = 340.3; //m/s
const int sensorAccuracy = 2; //2-200cm
const int sensorTimeout = ((float(sensorAccuracy)/soundSpeed)*2)*1000000;

void setup() 
{
  Serial.begin (9600);

  pinMode(triggerPin, OUTPUT);
  for(int echoPin = firstEchoPin ; echoPin <= lastEchoPin ; echoPin++ )
    pinMode(echoPin, INPUT);
}
 
void trigger()
{
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(triggerDuration);
    digitalWrite(triggerPin, LOW);
}

typedef struct SensorData
{
    int sensorNumber :3,
          measurment :10;
} SensorData;

void loop() 
{
    int duration;
    SensorData sensorData;
    memset(&sensorData, 0, sizeof(sensorData));

    for(int echoPin = firstEchoPin ; echoPin <= lastEchoPin ;  echoPin++)
    {
        trigger();

        duration = pulseIn(echoPin, HIGH, sensorTimeout);
        sensorData.measurment = int((duration / 2) / 29.1f);
        sensorData.sensorNumber = echoPin - firstEchoPin;
        Serial.write((uint8_t *)&sensorData, sizeof(sensorData));

        delay(delayBetweenMeasurments);
    }
}