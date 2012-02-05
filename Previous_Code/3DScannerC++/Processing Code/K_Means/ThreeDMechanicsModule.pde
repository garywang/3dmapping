/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

//Please note: Much of this code ought to be transfered to PVector. For debugging purposes, it will remain this way until the program works, though. NEEDSWORK

class Point2D
{
  Point2D(float x, float y)
  {
    this.x=x;
    this.y=y;
  };
  float x;
  float y;
};

class Point3D
{
  Point3D(float x, float y, float z)
  {
    this.x=x;
    this.y=y;
    this.z=z;
  };
  void Draw(float focal_length)
  {
    point(width/2+x*focal_length/z, height/2+y*focal_length/z);
  };
  float x;
  float y;
  float z;
  float Dot(Point3D other)
  {
    return this.x*other.x+this.y*other.y*this.z*other.z;
  };
  
  Point3D Cross(Point3D other)
  {
    return new Point3D(this.y*other.z-this.z*other.y, this.z*other.x-this.x*other.z, this.x*other.y-this.y*other.x);
  };
  
  Point3D Plus(Point3D other)
  {
    return new Point3D(this.x+other.x, this.y+other.y, this.z+other.z);
  };
  
  Point3D Minus(Point3D other)
  {
    return new Point3D(this.x-other.x, this.y-other.y, this.z-other.z);
  };
  
  Point3D Times(float amount)
  {
    return new Point3D(this.x*amount, this.y*amount, this.z*amount);
  };
};

class Line2D
{
  float r;
  float theta;
  Line2D(float r, float theta)
  {
    this.r=r;
    this.theta=theta;
  }
  Line2D(Point2D A,Point2D B)//Write and test NEEDSWORK
  {
    theta=atan((A.x-B.x)/(B.y-A.x));
    r=A.x*cos(theta)+A.y*sin(theta);
  }; 
  void Draw()//draws the line on the screen.
  {
    /*four relvant points on the line/edges of the screen.
    (0, r/sin(theta))
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

Point2D Intersect(Line2D A, Line2D B)
{
  return new Point2D(
  ((B.r*sin(A.theta)-A.r*sin(B.theta))/sin(A.theta-B.theta))
  ,
  ((B.r*cos(A.theta)-A.r*cos(B.theta))/sin(B.theta-A.theta))
  );
};

class Line3D
{
  Point3D point_on_line;
  Point3D direction;
  Line3D(Point3D point_a, Point3D point_b)
  {
    this.point_on_line=point_a;
    this.direction=point_b.Minus(point_a);
  };
};

class Plane3D
{
  Point3D on_plane;
  Point3D normal_vector;
  Plane3D(Point3D A, Point3D B, Point3D C)
  {
    on_plane=A;
    normal_vector=(B.Minus(A)).Cross(C.Minus(A));
  };
  Plane3D(Point3D on_plane, Point3D normal_vector)
  {
    this.on_plane=on_plane;
    this.normal_vector=normal_vector;
  };
  Point3D IntersectWith(Line3D Line)//If this gives a divide by zero error, the line is parallel to the plane (either in it or off it all the way).
  {
    return Line.point_on_line.Plus(Line.direction.Times(
    (normal_vector.Dot(on_plane.Minus(Line.point_on_line)))
    /
    (normal_vector.Dot(Line.direction))
    ));
  };
};
