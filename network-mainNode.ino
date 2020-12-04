// Libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiMulti.h>
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFiClientSecure.h>

// Pins declaration
const int cePin = 4;
const int csnPin = 5;
const int sckPin = 18;
const int misoPin = 19;
const int mosiPin = 23;

const int timeoutPeriod = 200;


const char* ssid = "Redmi";
const char* password = "174a4bf36308";
RF24 radio(cePin, csnPin);
const byte address[6] = "00001";

//Your Domain name with URL path or IP address with path
//https://dockme20201010041424.azurewebsites.net//api/Docks/dockNumber/true
const char* serverName = "https://dockme2.azurewebsites.net/api";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

//Global variables definition
int distance;
int dockNumber = 1;
String isTakenString = "true";
bool isTaken = true;
String header;
String call = (String)dockNumber + "/" + isTaken;
String payload;

void setup() {
    Serial.begin(115200);
    // Deserialize the JSON document
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);

    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    Serial.println();
    Serial.println();
}

void loop() {
    SPI.begin();
    delay(10);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
    delay(10);
  
    Serial.println("Radio Started...");
    Serial.println();
  
    if (radio.available()) {
      radio.read(&isTaken, sizeof(isTaken));
    }
  
    if (isTaken == true) {
      isTakenString = "true";
    }
    else {
      isTakenString = "false";
    }
  
    Serial.print("Message: ");
    Serial.println(isTakenString);
    delay(10);
    SPI.end();
    delay(10);
  
    StaticJsonDocument<200> doc;
    //Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;


      // HTTP GET METHOD
      Serial.println("https://dockme2.azurewebsites.net/api/Docks/1");
      http.begin("https://dockme2.azurewebsites.net/api/Docks/1");
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.print("[HTTPS]GET code: ");
        Serial.print(httpCode);
      }

      String payload = http.getString();
      Serial.println(payload);

      // Deserialize the JSON document
      DeserializationError error = deserializeJson(doc, payload);

      int jsonDockNumber = doc["dockNumber"];
      Serial.println(jsonDockNumber);

      String jsonIsTaken = doc["isTaken"];
      Serial.println(jsonIsTaken);

      String jsonIsReserved = doc["isReserved"];
      Serial.println(jsonIsReserved);

      Serial.println();

      // Free resources
      http.end();
      Serial.print("HTTP Closed");
      Serial.println();




      // HTTP PUT METHOD
      Serial.println("https://dockme2.azurewebsites.net/api/Docks/" + call);
      http.begin("https://dockme2.azurewebsites.net/api/Docks");
      http.addHeader("Content-Length", "0");
      http.addHeader("Content-Type", "application/json");
      String jsonPayload = "{'dockNumber': " + String(jsonDockNumber) + " ,'isTaken': " + String(isTakenString) + " ,'isReserved': " + String(true) + " }";
      Serial.println(jsonPayload);
      int httpResponseCode = http.PUT(jsonPayload);

      Serial.print("PUT Response Code: ");
      Serial.println(httpResponseCode);

      if (httpResponseCode < 0) {
        Serial.print("Error on sending PUT Request: ");
        Serial.println(httpResponseCode);
      }
      
      //Free resources
      http.end();
      Serial.print("HTTP Closed");
      Serial.println();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    delay(2000);
  }
}
