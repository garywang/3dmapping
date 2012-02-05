color black=color(0);

class EdgeCluster
{
  ArrayList members;
  EdgeCluster(ArrayList members)
  {
    this.members=members;
  };
  void Draw(int x, int y, color DrawIn)
  {
    for(int i=0; i<members.size(); i++)
    {
      Point2D p=(Point2D)(members.get(i));
      set(x+int(p.x),y+int(p.y),DrawIn);
    };
  };
  int Size()
  {
    return members.size();
  };
};

ArrayList Cluster(PImage Edges)
{
  ArrayList Clusters=new ArrayList();
  for(int y=0; y<Edges.height; y++)
    for(int x=0; x<Edges.width; x++)
      if(Edges.get(x,y)!=black)
        Clusters.add(new EdgeCluster(AddCluster(Edges, x, y)));
  return Clusters;
};

ArrayList AddCluster(PImage Edges, int x, int y)//returns the array of interconnected pixels
{
  ArrayList Cluster=new ArrayList();
  Cluster.add(new Point2D(x,y));
  Edges.set(x,y,black);
  for(int i=-1; i<=1; i++)
    for(int j=-1; j<=1; j++)
      if(
      (i!=0||j!=0)
      &&
      (x+i>=0)
      &&
      (x+i<Edges.width)
      &&
      (y+j>=0)
      &&
      (y+j<Edges.height)
      &&
      (Edges.get(x+i,y+j)!=black)
      )
      {
        ArrayList toAdd=AddCluster(Edges, x+i, y+j);
        for(int a=0; a<toAdd.size(); a++)
          Cluster.add(toAdd.get(a));
      };
  return Cluster;
};
