/*
 * Receiver Code
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
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
