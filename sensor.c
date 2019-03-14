#define NUMBER_OF_SENSORS 2

const int triggerPin = 2;
const int firstEchoPin = 3;
const int lastEchoPin = (firstEchoPin+NUMBER_OF_SENSORS)-1;

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
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
}

typedef struct SensorData
{
    int sensorNumber :3,
         measurment  :5;
} SensorData;

void loop() 
{
    int sensorNumber;
    int duration;
    SensorData sensorData;
    memset(&sensorData, 0, sizeof(sensorData));

    for(int echoPin = firstEchoPin ; echoPin <= lastEchoPin ;  echoPin++)
    {
        trigger();

        duration = pulseIn(echoPin, HIGH);
        sensorData.measurment = int((duration / 2) / 29.1f);
        
        Serial.write((uint8_t *)&sensorData, sizeof(sensorData));

        sensorNumber = echoPin - firstEchoPin;

        delay(100);
    }
}