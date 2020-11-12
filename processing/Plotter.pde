import processing.serial.*;
import java.util.*;

class Plotter {
  
  Serial port;
  
  boolean ready = true;  
  Queue<ArrayList<Byte>> codeQueue = new ArrayDeque<ArrayList<Byte>>();
  
  Plotter(PApplet app) {
    port = new Serial(app, Serial.list()[0], 9600);
    delay(5000);
  }
  
  void update() {
    if (port.available() >= 4) {
      ArrayList<Byte> reply = new ArrayList<Byte>();
      
      while(port.available() > 0) {
        reply.add((byte) port.read());
      }
      
      String s = "";
      for (int i = 0; i < 4; i++) {
        s += (char) reply.get(i).byteValue();
      }
      
      if ("done".equals(s)) {
        println("command compleate");
        ready = true;
      }//} else {
        String err = "";
        for (int i = 0; i < reply.size(); i++) {
          err += (char) reply.get(i).byteValue();
        }
        println(err);
        //exit();
      //}
    }
    
    if (ready && codeQueue.size() > 0) {
      //codeQueue.poll();
      //codeQueue.poll();
      println("sending" + codeQueue.peek());
      
      
      send(codeQueue.poll());
      ready = false;
    }
  }
  
  void start() {
    ArrayList<Byte> line = new ArrayList<Byte>();
    addCommand(line, "star");
    addUInt16(line, 0); // major
    addUInt16(line, 1); // minor
    addUInt16(line, 0); // patch
    addUInt16(line, 0); // mode
    codeQueue.offer(line);
  }
  
  void home() {
    ArrayList<Byte> line = new ArrayList<Byte>();
    addCommand(line, "home");
    addPadding(line, 8);
    codeQueue.offer(line);
  }
  
  void move(PVector v) {
    move(v.x, v.y);
  }
  
  void move(float x, float y) {
    ArrayList<Byte> line = new ArrayList<Byte>();
    addCommand(line, "move");
    addFloat32(line, x);
    addFloat32(line, y);
    codeQueue.offer(line);
  }
  
  void mark(PVector v) {
    mark(v.x, v.y);
  }
  
  void mark(float x, float y) {
    ArrayList<Byte> line = new ArrayList<Byte>();
    addCommand(line, "mark");
    addFloat32(line, x);
    addFloat32(line, y);
    codeQueue.offer(line);
  }
  
  int width() {
    return 2870;
  }
  
  int height() {
    return 2030;
  }
  
  void send(ArrayList<Byte> codeLine) {
    if (codeLine.size() != 12) {
      println("Error! Wrong code line size in send");
      exit();
    }
    for (int i = 0; i < codeLine.size(); ++i) {
      port.write(codeLine.get(i));
    }
  }
  
  void addCommand(ArrayList<Byte> line, String command) {
    for (int i = 0; i < command.length(); ++i) {
      line.add((byte) command.charAt(i));
    }
  }
  
  void addPadding(ArrayList<Byte> line, int amount) {
    for (int i = 0; i < amount; ++i) {
      line.add((byte) '\0');
    }
  }
  
  void addUInt16(ArrayList<Byte> line, int a) {
    if (a < 0 || a >= pow(2, 16)) {
      println("Error! Invalid value in addUInt16");
      exit();
    }
    
    byte[] bytes = new byte[] {
      (byte) (a & 0xff),
      (byte) ((a >> 8) & 0xff)
    };
    
    // little endian
    for (int i = 0; i < bytes.length; ++i) {
      line.add(bytes[i]);
    }
  }
  
  void addFloat32(ArrayList<Byte> line, float a) {
    // convert to bytes and little endian
    int intBits =  Float.floatToIntBits(a);
    byte[] bytes = new byte[] {
      (byte) ((intBits) & 0xff),
      (byte) ((intBits >> 8) & 0xff),
      (byte) ((intBits >> 16) & 0xff),
      (byte) ((intBits >> 24) & 0xff),
    };
    
    for (int i = 0; i < bytes.length; ++i) {
      line.add(bytes[i]);
    }
  }
  
}
