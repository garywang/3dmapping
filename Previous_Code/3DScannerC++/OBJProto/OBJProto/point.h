#ifndef _POINT_H_
#define _POINT_H_

#include <math.h>
struct Point2D
{
	double x;
	double y;
	Point2D(double X, double Y)
	{
		x=X;
		y=Y;
	};
	void Normalize()
	{
		double length=sqrt(x*x+y*y);
		x/=length;
		y/=length;
	};
};

struct Point3D
{
	double x;
	double y;
	double z;
	Point3D(double X, double Y, double Z)
	{
		x=X;
		y=Y;
		z=Z;
	};
	Point3D(Point2D* basis, double Z)
	{
		x=basis->x;
		y=basis->y;
		z=Z;
	};
	void Normalize()
	{
		double length=sqrt(x*x+y*y+z*z);
		x/=length;
		y/=length;
		z/=length;
	};
};

#endif