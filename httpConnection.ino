#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiMulti.h>
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <WiFiClientSecure.h>

const char* ssid = "Redmi";
const char* password = "174a4bf36308";

//Your Domain name with URL path or IP address with path
//https://dockme20201010041424.azurewebsites.net//api/Docks/dockNumber/true
const char* serverName = "https://dockme20201010041424.azurewebsites.net/api";

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
String isTaken = "false";
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
  StaticJsonDocument<200> doc;
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      //HTTP GET METHOD

        
        http.begin("https://dockme.azurewebsites.net/api/Docks/1");
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
        //Serial.println(payload.substring(payload.indexOf(":"), payload.indexOf(",")));

        // Free resources
        http.end();

        if(jsonIsTaken == "true"){
          jsonIsTaken = "false";
        }
        else{
          jsonIsTaken = "true";
        }

      // HTTP PUT METHOD
      
        // Your Domain name with URL path or IP address with path
        //Serial.print("https://dockme20201010041424.azurewebsites.net/api/Docks/1/false");
        Serial.println("https://dockme.azurewebsites.net/api/Docks/" + call);
        http.begin("https://dockme.azurewebsites.net/api/Docks");
        http.addHeader("Content-Length", "0");
        http.addHeader("Content-Type", "application/json");
        String jsonPayload = "{'dockNumber': " + String(jsonDockNumber) + " ,'isTaken': " + jsonIsTaken + " ,'isReserved': " + jsonIsReserved + " }";
        Serial.println(jsonPayload);
        int httpResponseCode = http.PUT(jsonPayload);

        //String response = http.getString();
        Serial.print("PUT Response Code: ");
        Serial.println(httpResponseCode);
        //Serial.println(response);

        if (httpResponseCode < 0){
        Serial.print("Error on sending PUT Request: ");
        Serial.println(httpResponseCode);
        }

        //http.addHeader("Content-Type", "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW");
        //https://dockme20201010041424.azurewebsites.net//api/Docks/3/false
        //int httpResponseCode = http.PUT("");
        //Serial.println();
        //Serial.print("HTTP Response code: ");
        //Serial.println(httpResponseCode);
      //Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    delay(2000);
  }
}
