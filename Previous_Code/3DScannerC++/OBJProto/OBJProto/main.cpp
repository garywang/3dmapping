#include <iostream>
using namespace std;

#include "linear_combination.h"

#include "pointcloud.h"

#include "line.h"

int main()
{
	list<Point2D>* points=new list<Point2D>;

	points->add(new Point2D(0,1));
	points->add(new Point2D(.1,.9));
	points->add(new Point2D(.2,.8));
	points->add(new Point2D(.3,.7));
	points->add(new Point2D(.4,.6));
	points->add(new Point2D(.5,.5));
	points->add(new Point2D(.6,.6));
	points->add(new Point2D(.7,.7));
	points->add(new Point2D(.8,.8));
	points->add(new Point2D(.9,.9));
	points->add(new Point2D(1,1));
	points->add(new Point2D(.1,1));
	points->add(new Point2D(.2,1));
	points->add(new Point2D(.3,1));
	points->add(new Point2D(.4,1));
	points->add(new Point2D(.5,1));
	points->add(new Point2D(.6,1));
	points->add(new Point2D(.7,1));
	points->add(new Point2D(.8,1));
	points->add(new Point2D(.9,1));


	//these lines would be detected by the Hough detector from points...
	line* v= new line(1,0,1);
	line* u= new line(-1.14,1.14,1);

	//the basis coordantes of the laser plane
	Point2D* unit_u=new Point2D(v->a(),v->b());
	Point2D* unit_v=new Point2D(u->a(),u->b());
	//the offset of the laser plane: use the x coord of intersection.
	double w_val=(u->b()-v->b())/(v->a()*u->b()-u->a()*v->b());

	/*build the cloud from the calculated quantities*/
	pointcloud* cloud= new pointcloud();
	for(int i=0; i<points->size(); i++)
		cloud->add(new Point3D(Combine(unit_u, unit_v, points->get(i)), w_val));

	SaveOBJ(cloud, "test.obj");

	return 0;
};