/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

/*
Preforms a simple image subraction.
B is subtracted from A.
Can be used to detect changes between frames.
A and B should be the same size.
*/
PImage Subtract(PImage A, PImage B)
{
  PImage Diffrence=new PImage(A.width, A.height);
  colorMode(RGB, 256);
  for(int x=0; x<A.width; x++)
  {
    for(int y=0; y<A.height; y++)
    {
      color ColorA=A.get(x,y);
      color ColorB=B.get(x,y);
      
      int r=(((ColorA>>16)&0xFF)-((ColorB>>16)&0xFF));
      if(r<0){r=0;}
      
      int g=(((ColorA>>8)&0xFF)-((ColorB>>8)&0xFF));
      if(g<0){g=0;}
      
      int b=((ColorA&0xFF)-(ColorB&0xFF));
      if(b<0){b=0;}
      
      Diffrence.set(x,y, color(r,g,b));
      
    }
  }
  return Diffrence;
};
