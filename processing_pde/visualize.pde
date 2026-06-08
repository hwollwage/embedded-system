import processing.serial.*;

Serial port;

float roll = 0;
float pitch = 0;

void setup() {
  size(1000, 700, P3D);

  printArray(Serial.list());

  port = new Serial(this, "/dev/ttyUSB0", 115200);
  port.bufferUntil('\n');
}

void draw() {
  background(20);

  lights();

  pushMatrix();

  translate(width/2, height/2);

  rotateZ(radians(roll));
  rotateX(radians(pitch));

  drawAirplane();

  popMatrix();

  fill(255);
  textSize(20);

  text("Roll  : " + nf(roll, 1, 2), 20, 30);
  text("Pitch : " + nf(pitch, 1, 2), 20, 60);
}

void serialEvent(Serial port) {

  String line = port.readStringUntil('\n');

  if (line == null) return;

  line = trim(line);

  String[] parts = split(line, ',');

  if (parts.length == 2) {
    roll  = float(parts[0]);
    pitch = float(parts[1]);
  }
}

void drawAirplane() {

  fill(180);

  // Body
  pushMatrix();
  box(250, 30, 30);
  popMatrix();

  // Wings
  pushMatrix();
  box(60, 8, 220);
  popMatrix();

  // Vertical Tail
  pushMatrix();
  translate(-100, -25, 0);
  box(25, 50, 8);
  popMatrix();

  // Horizontal Tail
  pushMatrix();
  translate(-100, 0, 0);
  box(25, 6, 90);
  popMatrix();

  // Nose
  pushMatrix();
  translate(140, 0, 0);
  sphere(18);
  popMatrix();
}