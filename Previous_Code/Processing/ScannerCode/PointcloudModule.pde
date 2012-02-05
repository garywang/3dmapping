/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

class PointCloud
{
  ArrayList  members=new ArrayList();
  void AddPoint(Point3D toadd)
  {
    members.add(toadd);
  };
  void SaveToFile(String filename)
  {
    /*Write the pointcloud to an .obj file...
    comments are of the form 
    #this is a comment    
    each point is written as
    v [x] [y] [z]
    */
    String[] lines = new String[members.size()+1];
    lines[0]="#Pointcloud generated using code by Will Oursler.";
    for (int i = 0; i < members.size(); i++) {
      Point3D p=(Point3D)members.get(i);
      lines[i+1] = "v "+p.x + " "+ p.y+" "+p.z;
    }
    saveStrings(filename+".obj", lines);
  };
};
