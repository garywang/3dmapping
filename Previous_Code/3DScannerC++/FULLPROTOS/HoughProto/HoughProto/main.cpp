/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

#include <iostream>
using namespace std;

#include "hough.h"

int main()
{
	HoughTransform hough=HoughTransform(5000,5000,LoadImage("blob.image"));
	cout<<"Hough is init-ed\n";

	double threshold=hough.Mass()*.01;
	list<line>* lines=hough.GetNBestLines(2,threshold);
	for(int i=0; i<lines->size(); i++)
		lines->get(i)->print();
	/*
	line* closest=hough.GetLineNearest(new line(-1,1,1),2,threshold);
	closest->print();*/
	return 0;
};