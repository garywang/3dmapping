PImage On;
PImage Off;
void setup() 
{
  Off=loadImage("Off.JPG");
  On=loadImage("On.JPG");
  size(On.width, On.height);
  noLoop();
}

void draw() 
{
  PImage Diffrence=Subtract(On, Off);
  image(Diffrence, 0, 0);
}
