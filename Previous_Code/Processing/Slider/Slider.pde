slider slide;

void setup() 
{
  size(200, 200);
  slide=new slider(width-5,0,height,5);
}

void draw() 
{ 
  background(slide.getValue());
  slide.Draw();
}

void mousePressed() {
  slide.MouseDown();
}

void mouseDragged() {
  slide.MouseMove();
}

void mouseReleased() {
  slide.MouseOff();
}

