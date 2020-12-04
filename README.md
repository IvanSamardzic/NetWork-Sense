## NetWork-Sense

* Low Power Consumption
* Energy Autonomy
* Wireless Communication Realisation Using Radio Vawes

### System Architecture

![GitHub Logo](https://www.researchgate.net/profile/Harmanpreet_Singh11/publication/316965453/figure/fig7/AS:668884814266372@1536485975197/Architecture-of-WSN-5.jpg)

#### Arduino Nano Pin Configuration

```
const int redLed = 2;
const int greenLed = 3;
const int cePin = 7;
const int csnPin = 8;
const int trigPin = 9;
const int echoPin = 10;
const int mosiPin = 11;
const int misoPin = 12;
const int sckPin = 13;
```

#### ESP32 Pin Configuration


```
const int cePin = 4;
const int csnPin = 5;
const int mosiPin = 23;
const int misoPin = 19;
const int sckPin = 18;
```

#### Network Explanation

The node has the function of monitoring the presence of the object at an angle of 45 degrees, when the vessel / vehicle is recognized by a sensor, then this status change
message is sent to the main node of the sensor network (gateway) using a radio module operating at 2.4 GHz.

When the master node receives a state change message on one of its child nodes, then the gateway sends a request to the database to change the value that determines the
occupancy of the position in front of the sensor.

###### Connection to WiFi Network
```
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
```
The gateway is equipped with an ESP32 microcontroller that has the ability to connect to a WiFi network, communicates with the database by sending various HTTP requests.The
ability to send HTTP requests is possible if the HTTP Client is properly created to receive and send data to the HTTP Server.

###### HTTP Client Initialisation 
```
//Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    // Measure the time the system tries to create HTTP Client or
    // time it has been created
    lastTime = millis();
    // Wait for 2000msec
    delay(2000);
  }

```

###### Sensor Data Acquisition And Conversion Into String

```
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
```

