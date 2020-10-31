import processing.serial.*;

Serial port;

void setup() {
  printArray(Serial.list());
  port = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  port.write(65);
  while (port.available() > 0) {
    int inByte = port.read();
    char c = (char)inByte;
    print(c);
  }
}
