/*
 * Transmitter Code
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int cePin = 7;
const int csnPin = 8;
const int mosiPin = 11;
const int misoPin = 12;
const int sckPin = 13;

int number = 0;

RF24 radio(cePin, csnPin);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  radio.write(&number, sizeof(number));
  Serial.print("Number: ");
  Serial.println(number);
  number++;
  delay(1000);
}
