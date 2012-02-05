/************************
*  Original Code (Beta) *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

PImage EdgeImage;

void setup() 
{
  //EdgeImage=loadImage("IdealGnome.bmp");
  //EdgeImage=loadImage("Edges.bmp");
  //EdgeImage=loadImage("test.bmp");
  //EdgeImage=loadImage("test2.bmp");
  EdgeImage=loadImage("Blobscan.png");
  EdgeImage.loadPixels();
  size(EdgeImage.width, EdgeImage.height);
  noLoop();
}

void draw() 
{     
  image(EdgeImage, 0, 0);//Draw the image to the screen
  HoughTransform Hough=new HoughTransform(EdgeImage,200, 200);
  //Hough.DrawTransform();
  stroke(color(255,255,0));//Draw bright yellow lines for the results.
  //Hough.GetBestLine().Draw();
  ArrayList Lines=Hough.GetLines(600);//100 for meanline data, 200 for test 2
  for(int i=0; i<Lines.size(); i++)
  {
    Line2D l=(Line2D)(Lines.get(i));
    l.Draw();
  };
}
class Line2D
{
  float r;
  float theta;
  Line2D(float r, float theta)
  {
    this.r=r;
    this.theta=theta;
  }
  //Line2D(Point2D,Point2D) Write and test NEEDSWORK
  void Draw()//draws the line on the screen.
  {
    //four relvant points on the line....
    /*(0, r/sin(theta))
    (r/cos(theta),0)
    (width,(r-width*cos(theta))/sin(theta))
    ((r-height*sin(theta))/cos(theta),height)*/
    
    //draw every possible combination of the above....
    line(0, r/sin(theta), r/cos(theta),0);
    line(0, r/sin(theta),width,(r-width*cos(theta))/sin(theta));
    line(0, r/sin(theta),(r-height*sin(theta))/cos(theta),height);
    
    line(r/cos(theta),0,width,(r-width*cos(theta))/sin(theta));    
    line(r/cos(theta),0,(r-height*sin(theta))/cos(theta),height);
    
    line(width,(r-width*cos(theta))/sin(theta),(r-height*sin(theta))/cos(theta),height);
  }
};

/*Uncomment and test this part...NEEDSWORK
Point2D Intersect(Line2D A, Line2D B)
{
  return new Point2D(
  ((B.r*sin(A.theta)-A.r*sin(b.theta))/sin(A.theta-B.theta))
  ,
  ((B.r*cos(A.theta)-A.r*cos(b.theta))/sin(B.theta-A.theta))
  );
};*/

class HoughTransform
{
  PImage _image;
  
  float  _rho_max;  //rho varies from 0 to _rho_max=sqrt(width^2+height^2)
  int    _rho_steps; 
                 //theta varies from 0 to 2*pi
  int    _theta_steps;
  
  int    _HoughArray[][];
  int    _NumPoints;
  
  HoughTransform(PImage Image, int RhoSteps, int ThetaSteps)
  {
    _image=Image;
    _rho_steps=RhoSteps;
    _theta_steps=ThetaSteps;
    _rho_max=_image.width+_image.height;//gurenteed upper bound
    _HoughArray=new int[_rho_steps][_theta_steps];
    for (int i = 0; i <_rho_steps; i++)
      for (int j = 0; j <_theta_steps; j++)
        _HoughArray[i][j] = 0;
    _NumPoints=0;
    
    //add all the live pixels.
    for(int x=0; x<_image.width; x++)
      for(int y=0; y<_image.height; y++)
        if(_image.get(x,y)!=color(0))
          AddPoint(x,y);
  }
  //HoughTransform(ArrayList Points, int RhoSteps, int ThetaSteps) Write and Test NEEDSWORK
  void AddPoint(int x, int y)
  {
    //add this eqn to the accumulator...
    //rho=y*sin(theta)+x*cos(theta)
    for(int step=0; step<_theta_steps; step++)
    {
      float theta=TWO_PI*step/_theta_steps;
      float rho=y*sin(theta)+x*cos(theta);
      if(rho>0)//if rho<0, the line will be addressed at another value of theta. Ignore it
        _HoughArray[int(rho*_rho_steps/_rho_max)][step]++;
      };
  }
  ArrayList GetLines(int ThresholdValue)//Get all lines above a certian threshold. Quick, but tends to produce multiple lines near strong segments.
  {
    ArrayList Lines=new ArrayList();
    for (int i = 0; i < _rho_steps; i++) {
      for (int j = 0; j < _theta_steps; j++) {
        if(_HoughArray[i][j]>ThresholdValue)
        {
          Lines.add(new Line2D(i*_rho_max/_rho_steps,j*TWO_PI/_theta_steps));
        }
      }
    }
    return Lines;
  };
  //ArrayList GetNBestLines(int n);//Use k means clustering to find the n best peaks in the data. Works best if n is large (>3) NEEDSWORK
  Line2D GetBestLine()//Gets the best line in the accumulator.
  {
    float theta=0;
    float rho=0;
    int Max=0;
    for (int i = 0; i < _rho_steps; i++) {
      for (int j = 0; j < _theta_steps; j++) {
        if(_HoughArray[i][j]>Max)
        {
          rho=i*_rho_max/_rho_steps;
          theta=j*TWO_PI/_theta_steps;
          Max=_HoughArray[i][j];
        }
      }
    }
    return new Line2D(rho,theta);
  };
  void DrawTransform()
  {
    for (int j = 0; j < _rho_steps; j++) {
      for (int i = 0; i < _theta_steps; i++) {
        stroke(_HoughArray[j][i]);//Theta along the x axis.
        point(i,j);
      }
    }
  }
}

