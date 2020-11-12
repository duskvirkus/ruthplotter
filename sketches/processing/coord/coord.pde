int w = 287;
int h = 203;

PVector pos;

int scale = 2;

final float stepsPerMM = 7.47169811321;

void settings() {
  size(w * scale, h * scale);
}

void setup() {
  pos = new PVector();
}

int getA(float x, float y) {
  return int((y * sqrt(2)) + (getB(x, y)));
}

int getB(float x, float y) {
  return int(((x - y) * sqrt(2) / 2));
}

void draw() {
  background(0);
  
  pos.x = mouseX / float(scale);
  pos.y = mouseY / float(scale);
  
  text("x=" + pos.x, 0, 10);
  text("y=" + pos.y, 0, 20);
  
  stroke(255);
  line(mouseX - 10, mouseY, mouseX + 10, mouseY);
  line(mouseX, mouseY - 10, mouseX, mouseY + 10);
 
 
  //stroke(255, 0, 0);
  //float m = (mouseX - mouseY) * sqrt(2) / 2;
  //float k = m * sqrt(2) / 2;
  ////println(mouseX - mouseY);
  ////println("a" + m);
  //line(mouseY, mouseY, mouseX, mouseY);
  //float j = mouseY + k;
  //line(0, mouseY, mouseY, mouseY);
  //line(0, 0, j, j);
  //line(j, j, j + k, j - k);
  
  float a = getA(pos.x, pos.y);
  float b = getB(pos.x, pos.y);
  
  text("a=" + int(a * stepsPerMM), 0, 30);
  
  push();
  rotate(PI / 4);
  stroke(255, 0, 0);
  line(0, 0, a * scale, 0);
  pop();
  
  text("b=" + int(b * stepsPerMM), 0, 40);
  
  push();
  rotate(PI / 4);
  stroke(0, 0, 255);
  line(a * scale, 0, a * scale, b * scale);
  pop();
}
