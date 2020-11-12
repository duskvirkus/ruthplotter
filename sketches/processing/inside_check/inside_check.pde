
int length1 = 1520;
int length2 = 1075;

int length3 = 2595;
int length4 = 445;
int m = length1 + length2;

PGraphics pg;

void settings() {
  size(length3/4, m/4);
}

boolean check(int x, int y) {
  if (x >= 0 && x <= length1 && y >= 0 && y <= length1) {
    if (y < x) {
      return true;
    }
  }
  
  if (x >= length1 && x <= length3 && y >= length4 && y <= length1) {
    if (y - length4 < length2 - (x - length1)) {
      return true;
    }
  }
  
  if (x >= 0 && x <= length2 && y >= -length2 && y <= 0) {
    if (y + length2 > length2 - x) {
      return true;
    }
  }
  
  if (x >= length2 && x <= length3 && y >= -length2 && y <= length4) {
    if (y + length2 > x - length2) {
      return true;
    }
  }
  
  return false;
}

void setup() {
  pg = createGraphics(length3, m);
  
  pg.beginDraw();
  
  pg.loadPixels();
  
  for (int x = 0; x < pg.width; x++) {
    
    for (int j = 0; j < pg.height; j++) {
      int y = j - length2;
      
      pg.pixels[x + (pg.height - (j + 1)) * pg.width] = check(x, y) ? color(0, 255, 0) : color(255, 0, 0);      
      
    }
    
  }
  
  pg.updatePixels();
  
  pg.endDraw();
  
  image(pg, 0, 0, width, height);
}
