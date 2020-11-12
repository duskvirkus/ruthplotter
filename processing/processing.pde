
boolean hidden = false;

Plotter p;

void setup() {
  p = new Plotter(this);
  p.start();
  
  p.home();
  
  int w = p.width();
  int h = p.height();
  
  int r = 200;
  for (int i = 0; i < 21; i++) {
    float a = map(i, 0, 20, 0, TWO_PI);
    float x = int(r * cos(a) + w / 2);
    float y = int(r * sin(a) + h / 2);
    
    if (i == 0) {
      p.move(x, y);
      println(x, y);
    } else {
      p.mark(x, y);
    }
  }
  
  //p.move(20,20);
  //p.mark(70, 20);
  //p.mark(70, 70);
  //p.mark(20, 70);
  //p.mark(20, 20);
  
  p.home();
}

void draw() {
  if(!hidden) {
    surface.setVisible(false); //This is what you're looking for.
    hidden = true;
  }
  
  p.update();
}
