#ifndef _POINTCLOUD_H_
#define _POINTCLOUD_H_

//dependancies
#include "list.h"
#include "point.h"
#include <fstream>

typedef list<Point3D> pointcloud;

void SaveOBJ(pointcloud* tosave, char* filename)
{
	ofstream objfile;
	objfile.open (filename);
	objfile<<"#vertices\n";
	for(int i=0; i<tosave->size(); i++)
	{
		Point3D* p=tosave->get(i);
		objfile<<"v "<<p->x<<" "<<p->y<<" "<<p->z<<"\n";
	};
	objfile.close();
};
#endif