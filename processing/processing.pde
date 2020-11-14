
boolean hidden = false;

Plotter p;

void setup() {
  p = new Plotter(this);
  p.start();
  
  p.home();
  
  int w = p.width();
  int h = p.height();
  
  for (int j = 0; j < 5; ++j) {
    int r = int(map(j, 0, 5, 50, 300));
    for (int i = 0; i < 201; i++) {
      float a = map(i, 0, 200, TWO_PI, 0);
      float x = int(((r * cos(a)))+ w / 2);
      float y = int(r * sin(a) + h / 2);
      
      if (i == 0) {
        p.move(x, y);
        println(x, y);
      } else {
        p.mark(x, y);
      }
    }
  }
  
  //p.move(20,20);
  //p.mark(70, 20);
  //p.mark(70, 70);
  //p.mark(20, 70);
  //p.mark(20, 20);
  
  //for (int i = 0; i < 5; i++) {
  //  int s = int(map(i, 0, 5, 50, 400));
  //  rectangle(300 - s / 2, 300 - s / 2, s, s);
  //}
  
  p.home();
}

void rectangle(int x, int y, int w, int h) {
  p.move(x, y);
  p.mark(x + w, y);
  p.mark(x + w, y + h);
  p.mark(x, y + h);
  p.mark(x, y);
}

void draw() {
  if(!hidden) {
    surface.setVisible(false); //This is what you're looking for.
    hidden = true;
  }
  
  p.update();
}
