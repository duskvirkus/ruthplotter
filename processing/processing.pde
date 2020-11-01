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
   .setPosition(100,50)
   .setSize(200,19)
   ;
   
  cp5.addButton("penUp")
   .setValue(0)
   .setPosition(100, 80)
   .setSize(200,19)
   ;
   
  cp5.addButton("penDown")
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

void penUp(int value) {
  port.write(toBytes("M05"));
}

void penDown(int value) {
  port.write(toBytes("M03"));
}

byte[] toBytes(String s) {
  byte[] arr = new byte[s.length()];
  for (int i = 0; i < s.length(); ++i) {
    arr[i] = (byte)s.charAt(i);
  }
  return arr;
}
