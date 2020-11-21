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

RF24 radio(cePin, csnPin);

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}
