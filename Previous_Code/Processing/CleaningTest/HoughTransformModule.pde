/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

class HoughTransform
{
  float  _rho_max;  //rho varies from 0 to _rho_max=sqrt(width^2+height^2)
  int    _rho_steps; 
                 //theta varies from 0 to 2*pi
  int    _theta_steps;
  
  int    _HoughArray[][];
  int    _NumPoints;
  
  HoughTransform(PImage Image, int RhoSteps, int ThetaSteps)
  {
    _rho_steps=RhoSteps;
    _theta_steps=ThetaSteps;
    _rho_max=Image.width+Image.height;//gurenteed upper bound
    _HoughArray=new int[_rho_steps][_theta_steps];
    for (int i = 0; i <_rho_steps; i++)
      for (int j = 0; j <_theta_steps; j++)
        _HoughArray[i][j] = 0;
    _NumPoints=0;
    
    //add all the live pixels.
    for(int x=0; x<Image.width; x++)
      for(int y=0; y<Image.height; y++)
        if(Image.get(x,y)!=color(0))
          AddPoint(x,y);
  }
  HoughTransform(ArrayList Points, int RhoSteps, int ThetaSteps, float RhoMax)
  {
    _rho_steps=RhoSteps;
    _theta_steps=ThetaSteps;
    _rho_max=RhoMax;
    
    _HoughArray=new int[_rho_steps][_theta_steps];
    for (int i = 0; i <_rho_steps; i++)
      for (int j = 0; j <_theta_steps; j++)
        _HoughArray[i][j] = 0;
    _NumPoints=0;
    
    for(int x=0; x<Points.size(); x++)
    {
      Point2D p=(Point2D)Points.get(x);
      AddPoint(int(p.x), int(p.y));
    };
  }
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

