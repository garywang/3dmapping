/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

class Scanner
{
  PinholeCamera Camera;
  ArrayList Ref2D;
  ArrayList Ref3D;
  /*Load the scanner's parameter's from file.
  *All these values are calculable,
  *but not easy to do on the computer.
  *This way the calculations can be
  *done on paper.
  */
  
  /*Dynamically Assigned Members*/
  PImage Off;
  PointCloud cloud;
  
  Scanner(String Filename)
  {
    Camera=new PinholeCamera(1f);//Set to a default value. This should be changed later by the file data.
    Ref2D=new ArrayList();//init ref point arrays
    Ref3D=new ArrayList();
    /* Points ought to be
      0  -  1
      |     |
      2  -  3
     /     /
    4  -  5
    */
    
    String file[]=loadStrings(Filename+".scanner");
    
    for(int index=0; index < file.length; index++)
    {
      String[] pieces = split(file[index], '.');
      if(pieces[0]=="FocalLength"){Camera.focal_length=int(pieces[1]);}
      else if(pieces[0]=="2D"){Ref2D.add(new Point2D(int(pieces[1]), int(pieces[2])));}
      else if(pieces[0]=="3D"){Ref3D.add(new Point3D(int(pieces[1]), int(pieces[2]), int(pieces[3])));}
      //otherwise, assume it's a comment of some sort.
    };
    
    cloud=new PointCloud();
  }
  
  void SetOffImage(PImage toSet)
  {
    Off=toSet;
  };
  
  void ProcessImage(PImage On)
  {    
    ArrayList points=GetMeanline(ThresholdGreen(Subtract(On,Off),40));//Get an array of points from the image to intersect with the laser plane.
    
    Point3D LaserNormal=((Point3D)Ref3D.get(1)).Minus((Point3D)Ref3D.get(0));
    Plane3D BackPlane=new Plane3D((Point3D)Ref3D.get(0),(Point3D)Ref3D.get(1),(Point3D)Ref3D.get(2));
    Line2D LaserLine=(new HoughTransform(points,200,200, Off.width+Off.height)).GetBestLine(); //This needs reliable meanline data to work. Make sure that part works...
    Point3D PointOnLaserPlane=BackPlane.IntersectWith(Camera.GetLine(Intersect(new Line2D((Point2D)Ref2D.get(0),(Point2D)Ref2D.get(1)), LaserLine)));
    Plane3D LaserPlane=new Plane3D(PointOnLaserPlane, LaserNormal);
      
    for(int j=0; j<points.size(); j++)
    {
      cloud.AddPoint(LaserPlane.IntersectWith(Camera.GetLine((Point2D)points.get(j))));
    }; 
  };
  
  PointCloud GetCloud()
  {
    return cloud;
  };
};
