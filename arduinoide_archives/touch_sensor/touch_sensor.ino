// Define the Arduino pins
const int TOUCH_IO_PIN = 2;   // Connect the sensor's I/O pin here
const int LED_PIN     = 4;  // Uses the built-in Arduino LED

void setup() {
  Serial.begin(9600);              // Start communication with your computer
  pinMode(TOUCH_IO_PIN, INPUT);    // Set the sensor pin as an input
  pinMode(LED_PIN, OUTPUT);        // Set the LED pin as an output
}

void loop() {
  // Read the status of the I/O pin (HIGH or LOW)
  int touchState = digitalRead(TOUCH_IO_PIN);

  if (touchState == HIGH) {
    digitalWrite(LED_PIN, HIGH);   // Turn on the LED
    Serial.println("Touched");     // Print message to Serial Monitor
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn off the LED
    Serial.println("Not Touched"); 
  }

  delay(50); // Small pause to prevent text flooding
}
