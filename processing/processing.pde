import controlP5.*;
import processing.serial.*;

Serial port;
ControlP5 cp5;

void setup() {
  size(400, 400);
  
  printArray(Serial.list());
  port = new Serial(this, Serial.list()[0], 9600);
  
  cp5 = new ControlP5(this);
  
  cp5.addButton("home")
   .setValue(0)
   .setPosition(100,100)
   .setSize(200,19)
   ;
  
}

void draw() {
  while (port.available() > 0) {
    int inByte = port.read();
    char c = (char)inByte;
    print(c);
  }
}

void home(int value) {
  port.write(toBytes("G28"));
}

byte[] toBytes(String s) {
  byte[] arr = new byte[s.length()];
  for (int i = 0; i < s.length(); ++i) {
    arr[i] = (byte)s.charAt(i);
  }
  return arr;
}
