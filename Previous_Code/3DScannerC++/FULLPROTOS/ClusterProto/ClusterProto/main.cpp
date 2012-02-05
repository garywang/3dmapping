/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

#include <iostream>
using namespace std;

#include "Cluster.h"

class Point2D:public datapoint
{
private:
	double _x;
	double _y;
	double _weight;
public:
	Point2D(double x, double y, double weight){
		_x=x;
		_y=y;
		_weight=weight;
	};
	double distance(datapoint* rhs)
	{
		Point2D* other=(Point2D*)rhs;
		return sqrt(pow(this->x()-other->x(),2)+pow(this->y()-other->y(),2));
	};
	double x()
	{
		return _x;
	};
	double y()
	{
		return _y;
	};
	double weight()
	{
		return _weight;
	};
	datapoint* centroid(list<datapoint>* data)
	{
		double x=0;
		double y=0;
		double weight=0;
		for(int i=0; i<data->size(); i++)
		{
			Point2D* curr=(Point2D*)(data->get(i));
			x+=curr->x();
			y+=curr->y();
			weight+=curr->weight();
		};
		x/=weight;
		y/=weight;
		return new Point2D(x,y,weight);
	};
};

void Print(list<cluster>* toPrint)
{
	for(int i=0; i<toPrint->size(); i++)
	{
		cout<<"Cluster #"<<i+1<<endl;
		cluster* Cluster=toPrint->get(i);
		for(int j=0; j<Cluster->size(); j++)
		{
			Point2D* Point=(Point2D*)(Cluster->get(j));
			cout<<"("<<Point->x()<<","<<Point->y()<<")"<<endl;
		};
		cout<<endl;
	};
};

int main()
{
	/*one cluster*/
	cluster* one=new cluster(false);//when the program is done with this, all member data can be deleted.
	one->add(new Point2D(0.1,0.2,1));
	one->add(new Point2D(5.4,1.1,1));
	one->add(new Point2D(7.8,8.5,1));
	one->add(new Point2D(8.2,9.4,1));
	one->add(new Point2D(0.3,1.2,1));
	one->add(new Point2D(6.1,0.5,1));
	one->add(new Point2D(1.2,1.1,1));
	one->add(new Point2D(9.1,8.2,1));
	one->add(new Point2D(5.2,0.1,1));
	one->add(new Point2D(7.1,8.9,1));
	one->add(new Point2D(20.2,18.6,1));
	one->add(new Point2D(19.6,21.2,1));
	one->add(new Point2D(17.5, 21.2,1));

	Print(KMeans(one,7));
	return 0;
};