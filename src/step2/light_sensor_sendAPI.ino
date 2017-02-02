#include <Arduino.h>
#include <SPI.h>
#include <Ethernet2.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//HUEのipアドレス
char server[] = "192.168.1.41";
//Arduinoのipアドレス
IPAddress ip(192, 168, 1, 100);
EthernetClient client;

const int light_sensor = A0;
const int led_light   = 7;
int setValue = 400;

void setup()
{
    pinMode(led_light, OUTPUT);
    Serial.begin(9600);

    if (Ethernet.begin(mac) == 0) {
     Ethernet.begin(mac, ip);
   }
}

void loop()
{
    int sensorValue = analogRead(light_sensor);
    Serial.println(sensorValue);

    sendData(sensorValue);

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

void sendData(int data)
{

    if(data < setValue)
    {
        client.connect(server, 80);
        String s = "{\"on\":true}";
        Serial.println("connected");
        client.println("PUT /api/phYo8RzEFFZIwCv4lXMUw9BkxqqLHq7-GFL6qztR/lights/3/state HTTP/1.1");
        client.println("Host: 192.168.1.41");
        client.println("Content-Length: " + String(s.length()));
        Serial.println("Content-Length: " + String(s.length()));
        client.println("");
        client.println(s);
        Serial.println(s);
        client.stop();
    }
    else
    {
        client.connect(server, 80);
        String s = "{\"on\":false}";
        Serial.println("connected");
        client.println("PUT /api/phYo8RzEFFZIwCv4lXMUw9BkxqqLHq7-GFL6qztR/lights/3/state HTTP/1.1");
        client.println("Host: 192.168.1.41");
        client.println("Content-Length: " + String(s.length()));
        Serial.println("Content-Length: " + String(s.length()));
        client.println("");
        client.println(s);
        Serial.println(s);
        client.stop();
    }

    delay(1000);
}
