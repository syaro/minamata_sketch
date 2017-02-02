#include <Arduino.h>

const int light_sensor = A0;
const int led_light   = 7;

int setValue = 400;

void setup()
{
    pinMode(led_light, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int sensorValue = analogRead(light_sensor);
    Serial.println(sensorValue);

    if(sensorValue < setValue)
    {
        digitalWrite(led_light, HIGH);
        Serial.println("暗いよ");
    }
    else
    {
        digitalWrite(led_light, LOW);
        Serial.println("明るいよ");
    }
    delay(1000);
}
