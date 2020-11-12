void lerpLine(float x1, float y1, float x2, float y2) {
  
  float d = dist(x1, y1, x2, y2);
  
  int px = 0;
  int py = 0;
  
  for (int i = 0; i < d; i++) {
    float amt = i / d;
    
    int x = int(lerp(x1, x2, amt));
    int y = int(lerp(y1, y2, amt));
    
    point(x, y);
    
    //if (i > 0) {
    //  int a = x - px;
    //  if (!(a == 0 || a == -1 || a == 1)) {
    //    println("x = " + x + " px = " + px);
    //    println(x - px);
    //  }
      
    //  //println(y - py);
    //}
    
    px = x;
    py = y;
  }
}

void setup() {
  size(400, 400);
}

void draw() {
  background(255);
  
  //stroke(255, 0, 0);
  //line(width/2, height/2, mouseX, mouseY);
  
  stroke(0, 255, 0);
  lerpLine(width/2, height/2, mouseX, mouseY);
}
