/*Classes for clustering in 2D*/
class datapoint
{
  datapoint(Point2D location, float weight)
  {
    this.location=location;
    this.weight=weight;
  };
  Point2D location;
  float weight;
  void Draw()
  {
    stroke(weight);
    point(location.x,location.y);
  };
  Point2D GetLocation()
  {
    return location;
  };
  float GetWeight()
  {
    return weight;
  };
};

float distance(datapoint a, datapoint b)
{
  return abs(a.GetLocation().x-b.GetLocation().x)+abs(a.GetLocation().y-b.GetLocation().y);
};
class cluster
{
  cluster(ArrayList members)
  {
    this.members=members;
  };
  ArrayList members;
  datapoint GetSummary()//returns a datpoint with position a weighted mean of the members, and weight the sum of their weights.
  {
    float x=0;
    float y=0;
    float weight=0;
    for (int i=0; i<members.size(); i++) { 
      datapoint datum = (datapoint) members.get(i);
      x+=(datum.GetLocation().x)*(datum.GetWeight());
      y+=(datum.GetLocation().y)*(datum.GetWeight());
      weight+=(datum.GetWeight());
    };
    x/=weight;
    y/=weight;
    return new datapoint(new Point2D(x,y), weight);
  };
  void Draw()
  {
    for (int i=0; i<members.size(); i++)
    ((datapoint)members.get(i)).Draw();
    stroke(random(255),random(255),random(255));
    Point2D location=this.GetSummary().GetLocation();
    rect(location.x-1,location.y-1,2,2);
  };
  void Add(datapoint toadd)
  {
    members.add(toadd);
  };
};

ArrayList KMeans(ArrayList clusters)
{
  boolean SteadyState=true;
  do{
    ArrayList cluster_centers=new ArrayList();
    for(int i=0; i<clusters.size(); i++)
      cluster_centers.add(((cluster)clusters.get(i)).GetSummary());
    //make list of proxy clusters
    SteadyState=true;//assume steady state until demonstrated otherwise.
    for(int i=0; i<clusters.size(); i++)
    {
      cluster current=(cluster)clusters.get(i);
      for(int j=0; j<current.members.size(); j++)
      {
        //find the nearest cluster center 
          //If this is a diffrent cluster from the cluster of orgin
            //SteadyState=false;
          //Assign to the new version of the cluster
      }
    }
    //replace clusters with new versions.
  }while(!SteadyState);
  return clusters;
};

cluster C;
void setup() {
  size(500, 500);
  ArrayList points = new ArrayList();
  for(int i=0; i<(width*height)/30; i++)
    points.add(new datapoint(new Point2D(random(width),random(height)),100));
  C=new cluster(points);
  background(0);
}


void draw() {
  C.Draw();
}
