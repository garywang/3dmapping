/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

class PinholeCamera
{
  float focal_length;
  PinholeCamera(float focal_length)
  {
    this.focal_length=focal_length;
  };
  Point3D GetPoint(Point2D Image, float distance_from_camera)
  {
    float z=distance_from_camera*focal_length/sqrt(focal_length*focal_length+Image.x*Image.x+Image.y*Image.y);
    float x=Image.x*z/focal_length;
    float y=Image.y*z/focal_length;
    return new Point3D(x,y,z);
  };
  Line3D GetLine(Point2D Image)
  {
    return new Line3D(new Point3D(0,0,0), new Point3D(Image.x, Image.y, focal_length));//The line passes through the camera orgin and the point on the image plane.
  };
};
