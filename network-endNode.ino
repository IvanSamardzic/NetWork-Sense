// Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <avr/wdt.h>

// Pins declaration
const int redLed = 2;
const int greenLed = 3;
const int cePin = 7;
const int csnPin = 8;
const int trigPin = 9;
const int echoPin = 10;
const int mosiPin = 11;
const int misoPin = 12;
const int sckPin = 13;

// Variables declaration
int duration, distance;
const int delayPeriod = 10;
const int distanceLevel = 100;
const int timeoutPeriod = 200;
double conversionFactor = 0.017;
bool isTaken = false;


RF24 radio(cePin, csnPin); // CE, CSN
const byte address[6] = "00001";

void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
void setup() {
  Serial.begin(115200);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
}

void loop() {
  delay(timeoutPeriod);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(delayPeriod/5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(delayPeriod);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * conversionFactor;
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance < distanceLevel){
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    isTaken = true;
  }
  else{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    isTaken = false;
  }
  
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  radio.write(&isTaken, sizeof(isTaken));
  Serial.print("Message: ");
  Serial.println(isTaken);
  reboot();
}
