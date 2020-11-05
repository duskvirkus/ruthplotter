import processing.serial.*;
import java.lang.Exception;

enum PLOTTER_MODE {
  STREAM(0),
  DEBUG(1);
  
  private int val;
  
  private PLOTTER_MODE(int val) {
    this.val = val;
  }
  
  int get() {
    return val;
  }
}

enum COMMAND {
  START("sta"),
  HOME("hom"),
  CHANGE_MODE("cmo"),
  MOVE("mov"),
  MARK("mar"),
  INFORMATION("inf");
  
  private String command;
  
  private COMMAND(String command) {
    this.command = command;
  }
  
  String get() {
    return command;
  }
}

enum INFO_CODE {
  GENERAL(0),
  MODE(1),
  POSITION(2);
  
  private int val;
  
  private INFO_CODE(int val) {
    this.val = val;
  }
  
  int get() {
    return val;
  }
}

final int VERSION_MAJOR = 0;
final int VERSION_MINOR = 0;
final int VERSION_PATCH = 0;

class Plotter {
  
  Serial port;
  
  Plotter(PApplet app) throws Exception {
    printArray(Serial.list());
    port = new Serial(app, Serial.list()[0], 9600);
    
    begin();
  }
  
  void begin() throws Exception {
    sendCommand(COMMAND.START);
    //sendCommand(Command.START);
    sendUInt16(VERSION_MAJOR);
    sendUInt16(VERSION_MINOR);
    sendUInt16(VERSION_PATCH);
    sendUInt16(PLOTTER_MODE.DEBUG);
  }
  
  void home() {
    sendCommand(COMMAND.HOME);
    //sendCommand(Command.HOME);
  }
  
  void changeMode(PLOTTER_MODE m) throws Exception {
    sendUInt16(m);
  }
  
  void move(float x, float y) {
    move(new PVector(x, y));
  }
  
  void move(PVector v) {
    sendCommand(COMMAND.MOVE);
    //sendCommand(Command.MOVE_CMD);
    sendPosition(v);
  }
  
  void mark(float x, float y) {
    mark(new PVector(x, y));
  }
  
  void mark(PVector v) {
    sendCommand(COMMAND.MARK);
    //sendCommand(Command.MARK);
    sendPosition(v);
  }
  
  PLOTTER_MODE getMode() throws Exception {
    sendCommand(COMMAND.INFORMATION);
    //sendCommand(Command.INFORMATION);
    sendUInt16(INFO_CODE.MODE);
    
    //reply = awaitReply();
    return null;
  }
  
  PVector getPosition() throws Exception {
    sendCommand(COMMAND.INFORMATION);
    //sendCommand(Command.INFORMATION);
    sendUInt16(INFO_CODE.POSITION);
    
    return null;
  }
  
  // -----
  
  void sendCommand(COMMAND c) {
    println(c);
    port.write(c.get());
  }
  
  void sendUInt16(PLOTTER_MODE a) throws Exception {
    sendUInt16(a.get());
  }
  
  void sendUInt16(INFO_CODE a) throws Exception {
    sendUInt16(a.get());
  }
  
  void sendUInt16(int a) throws Exception {
    //println("sending" + a);
    
    // check bounds
    if (a < 0 || a >= pow(2, 16)) {
      throw new Exception("Invalid value in sendUInt16");
    }
    
    byte[] bytes = new byte[] {
      (byte) (a & 0xff),
      (byte) ((a >> 8) & 0xff)
    };
    
    // little endian
    
    //System.out.println(Arrays.toString(bytes));
    for (int i = 0; i < bytes.length; ++i) {
      port.write(bytes[i]);
    }
  }
  
  void sendFloat32(float a) {
    //println("sending" + a);
    
    // convert to bytes and little endian
    
    int intBits =  Float.floatToIntBits(a);
    byte[] bytes = new byte[] {
      (byte) ((intBits) & 0xff),
      (byte) ((intBits >> 8) & 0xff),
      (byte) ((intBits >> 16) & 0xff),
      (byte) ((intBits >> 24) & 0xff),
    };
    
    //System.out.println(Arrays.toString(bytes));
    for (int i = 0; i < bytes.length; ++i) {
      port.write(bytes[i]);
    }
  }
  
  void sendPosition(PVector v) {
    sendFloat32(v.x);
    sendFloat32(v.y);
  }
  
  //void awaitReply() {
    
  //}
  
}
