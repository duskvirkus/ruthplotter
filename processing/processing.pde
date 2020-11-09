
boolean hidden = false;

Plotter p;

void setup() {
  p = new Plotter(this);
  p.start();
  
  p.home();
}

void draw() {
  if(!hidden) {
    surface.setVisible(false); //This is what you're looking for.
    hidden = true;
  }
  
  p.update();
}
