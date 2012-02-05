PImage GreenThresholdFilter(PImage Raw, int threshold)
{
  PImage Green=new PImage(Raw.width, Raw.height);
  for(int i=0; i<Green.pixels.length; i++)
  {
    int G=(Raw.pixels[i] >> 8)& 0xFF;
    if(G<threshold) G=0;
    Green.pixels[i]=color(0,G,0);
  };
  Green.updatePixels();
  return Green;
};
PImage MeanLine(PImage Edges)
{
  PImage MeanLine=new PImage(Edges.width, Edges.height);
  MeanLine.loadPixels();
  color black=color(0);
  for(int y=0; y<Edges.height; y++)
  {
    int sumx=0;//take a mean to start...this really should be a median(or other noise resistant stat) NEEDSWORK
    int numx=0;
    for(int x=0; x<Edges.width; x++)
    {
      if(Edges.get(x,y)!=black)
      {
        sumx+=x;
        numx++;
      };
    };
    if(numx>0)MeanLine.set(sumx/numx,y,color(0,0,255));//Make the line blue...
  };
  return MeanLine;
};

