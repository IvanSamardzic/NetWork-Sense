const int redLed = 2;
const int greenLed = 3;
const int trigPin = 9;
const int echoPin = 10;
int duration, distance;
const int delayPeriod = 10;
const int distanceLevel = 70;
const int timeoutPeriod = 100;
double conversionFactor = 0.017;

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
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
  }
  else{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  delay(timeoutPeriod);
}
