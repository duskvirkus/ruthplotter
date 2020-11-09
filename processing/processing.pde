import controlP5.*;
import java.util.*;
import java.nio.ByteBuffer;

ControlP5 cp5;

Plotter p;

//boolean intialized = false;

void setup() {
  size(400, 600);
  
  try {
    p = new Plotter(this);
  } catch(Exception e) {
    e.printStackTrace();
  }
  
  
  
  //cp5 = new ControlP5(this);
  
  //cp5.addButton("home")
  // .setValue(0)
  // .setPosition(100,50)
  // .setSize(200,19)
  // ;
   
  //cp5.addButton("penUp")
  // .setValue(0)
  // .setPosition(100, 80)
  // .setSize(200,19)
  // ;
   
  //cp5.addButton("penDown")
  // .setValue(0)
  // .setPosition(100,100)
  // .setSize(200,19)
  // ;
     
  //cp5.addButton("positionAbsolute")
  // .setValue(0)
  // .setPosition(100,130)
  // .setSize(200,19)
  // ;
   
  //cp5.addButton("positionRelative")
  // .setValue(0)
  // .setPosition(100,150)
  // .setSize(200,19)
  // ;
   
  //PVector gridStart = new PVector(100, 200);
  //int gridSize = 40;
  
  //PVector[] indexs = new PVector[16];
  //indexs[0] = new PVector(0, 0);
  //indexs[1] = new PVector(0, 2);
  //indexs[2] = new PVector(0, 4);
  //indexs[3] = new PVector(1, 1);
  //indexs[4] = new PVector(1, 2);
  //indexs[5] = new PVector(1, 3);
  //indexs[6] = new PVector(2, 0);
  //indexs[7] = new PVector(2, 1);
  //indexs[8] = new PVector(2, 3);
  //indexs[9] = new PVector(2, 4);
  //indexs[10] = new PVector(3, 1);
  //indexs[11] = new PVector(3, 2);
  //indexs[12] = new PVector(3, 3);
  //indexs[13] = new PVector(4, 0);
  //indexs[14] = new PVector(4, 2);
  //indexs[15] = new PVector(4, 4);
  //String[] labels = new String[]{
  //  "upLeft10",
  //  "up10",
  //  "upRight10",
  //  "upLeft",
  //  "up",
  //  "upRight",
  //  "left10",
  //  "left",
  //  "right",
  //  "right10",
  //  "downLeft",
  //  "down",
  //  "downRight",
  //  "downLeft10",
  //  "down10",
  //  "downRight10"
  //};
  
  //for (int i = 0; i < labels.length; ++i) {
  //  cp5.addButton(labels[i])
  //   .setValue(0)
  //   .setPosition(gridStart.x + gridSize * indexs[i].x, gridStart.y + gridSize * indexs[i].y)
  //   .setSize(gridSize, gridSize)
  //   ;
  //}
  
  //startPlotter();
  
  //intialized = true;
}

void draw() {
  while (p.port.available() > 0) {
    int inByte = p.port.read();
    char c = (char)inByte;
    print(c);
  }
}





//void home(

//void home(int value) {
//  port.write(toBytes("G28"));
//}

//void penUp(int value) {
//  port.write(toBytes("M05"));
//}

//void penDown(int value) {
//  port.write(toBytes("M03"));
//}

//void positionAbsolute(int value) {
//  port.write(toBytes("G90"));
//}

//void positionRelative(int value) {
//  port.write(toBytes("G91"));
//}

//void downRight(int value) {
//  PVector v = getPosition();
//  println(v.x, v.y);
//  v.x++;
//  v.y++;
//  sendMove(v);
//}

//void sendMove(PVector v) {
  
//}

//PVector getPosition() {
//  if (!intialized) {
//    return new PVector(-1, -1);
//  }
  
//  port.write(toBytes("M114"));
  
//  while (port.available() < 9) {
//    delay(10);
//  }
  
//  ArrayList<Byte> buffer = new ArrayList<Byte>();
//  while (port.available() > 0) {
//    int inByte = port.read();
//    buffer.add((byte) inByte);
//  }
  
//  byte[] check = new byte[]{'R', 'M', '1', '1', '4'};
//  for (int i = 0; i < check.length; ++i) {
//    if (buffer.get(i) != check[i]) {
//      println("Invaild reply to M114");
//      exit();
//    }
//  }
  
//  return new PVector(floatFromBytes(buffer, 5, 7), floatFromBytes(buffer, 7, 9));
//}

//float floatFromBytes(ArrayList<Byte> bytes, int start, int end) {
//  byte[] b = new byte[end - start];
//  for (int i = start; i < end; i++) {
//    b[i - start] = bytes.get(i);
//  }
//  println(b);
//  return floatFromBytes(b);
//}

//float floatFromBytes(byte[] bytes) {
//  return ByteBuffer.wrap(bytes).getFloat();
//}

//byte[] toBytes(String s) {
//  byte[] arr = new byte[s.length()];
//  for (int i = 0; i < s.length(); ++i) {
//    arr[i] = (byte)s.charAt(i);
//  }
//  return arr;
//}
