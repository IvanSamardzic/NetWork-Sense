const int redLed = 2;
const int greenLed = 3;

void setup(){
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
}


void loop(){
  digitalWrite(redLed, HIGH);
  delay(500);
  digitalWrite(greenLed, HIGH);
  delay(500);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  delay(500);
}
