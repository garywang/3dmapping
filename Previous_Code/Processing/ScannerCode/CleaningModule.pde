/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

//This module does not work. NEEDSWORK
ArrayList GetMeanline(PImage Raw)//Takes the diffrence image and cleans it, returning a set of points in two dimensions that ought to be from the laser.
//This is a temporary approximation to find a rough meanline for the laser.
//For each row of pixels, find the x position of the median pixel. This really ought to do some sort of clustering... NEEDSWORK
{
  ArrayList MedianPixels=new ArrayList();
  colorMode(RGB, 256);
  color black=color(0,0,0);
  for(int y=0; y<Raw.height; y++)//on each row...
  {
    //Make sure there's at least one live pixel in the row...
    int RowEmpty=0;
    int i=0;
    while(i<Raw.width)
    {
      if(Raw.get(i,y)!=black)
      {
        RowEmpty=1;
        break;
      }
    }
    
    //If the row has live pixels...
    if(RowEmpty==1)
    {
      //init first and last pixels
      int first=0;
      while(Raw.get(first,y)==black)
        first++;
      int last=Raw.width-1;
      while(Raw.get(last,y)==black)
        last--;
      while(first<last)//the median pixel hasn't yet been found...
      {
        //find next live pixels.
        do{
          first++;
        }while(Raw.get(first,y)==black);
        do{
          last--;
        }while(Raw.get(last,y)==black);
      }
      MedianPixels.add(new Point2D((float)(first+last)/2,(float)y));
      stroke(color(0,0,255));
      point((float)(first+last)/2,(float)y);//Draw as a diagnostic.
    }
  }
  return MedianPixels;
};

PImage ThresholdGreen(PImage Raw, int Break)//Threshholds to white and black based on only the green component (because the laser is green). Break should be between 0 and 255.
{
  PImage Result=new PImage(Raw.width, Raw.height);
  colorMode(RGB, 256);
  for(int x=0; x<Raw.width; x++)
  {
    for(int y=0; y<Raw.height; y++)
    {
      color Color=Raw.get(x,y);      
      int g=((Color>>8)&0xFF);
      if(g>Break){      
        Result.set(x,y, color(255,255,255));
      }
      else{
        Result.set(x,y, color(0,0,0));
      }     
    }
  }
  return Result;
};
