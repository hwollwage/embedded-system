const int analogPin = A0;
const int digitalPin = 13;
const int led = 8;
const int buzzer = 9;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int state = digitalRead(digitalPin);
  float gasLevel = analogRead(analogPin);

  digitalWrite(led, !state);
  
  if(!state) {
    digitalWrite(buzzer, HIGH);
  }else {
    digitalWrite(buzzer, LOW);
  }

  Serial.print("gas level: ");
  Serial.println(gasLevel);

  delay(100);
}