const int lightPin = A5;
const int digitalPin = 8;
const int led = 9;

void setup() {
  Serial.begin(9600);
  pinMode(digitalPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {

  int light = analogRead(lightPin);
  
  if(light <= 400) {
    Serial.println("its day");
    digitalWrite(led, HIGH);
  }else {
    Serial.println("its night");
    digitalWrite(led, LOW);
  }

  Serial.print("light level: ");
  Serial.println(light);

  delay(200);
}