/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

#ifndef _LINE_H_
#define _LINE_H_

#include "cluster.h"

class line:public datapoint
{

	//a line of form ax+by=1
private:
	double _a;
	double _b;
	double _weight;
public:
	double a(){return _a;};
	double b(){return _b;};
	double weight(){return _weight;};
	line(double a, double b, double c, double weight)/*ax+by=c*/
	{
		_a=a/c;
		_b=b/c;
		_weight=weight;
	}
	double distance(datapoint *rhs)
	{
		line* other=(line*)rhs;
		//Uses Manhattan distance for speed.
		return fabs(this->a()-other->a())+fabs(this->b()-other->b());
	};
	datapoint* centroid(list<datapoint>* data)
	{
		double a=0;
		double b=0;
		double weight=0;
		for(int i=0; i<data->size(); i++)
		{
			line* curr=(line*)(data->get(i));
			a+=curr->weight()*curr->a();
			b+=curr->weight()*curr->b();
			weight+=curr->weight();
		};
		a/=weight;
		b/=weight;
		return new line(a,b,1,weight);
	};
	void print()
	{
		cout<<this->a()<<"x+"<<this->b()<<"y=1\n";
		//for debugging....
		cout<<"y="<<(-1)*a()/b()<<"x+"<<1/b()<<"\n";
	};
};
#endif