const int flamePin = 8;
const int led = 13;
const int buzzer = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(flamePin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int flameState = digitalRead(flamePin);
  
  if(flameState == LOW) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);
    Serial.println("flame detected");
  }else {
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    Serial.println("no flame");
  }
  delay(100);
}
