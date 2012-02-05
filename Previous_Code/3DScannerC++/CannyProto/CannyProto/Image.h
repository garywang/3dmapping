#ifndef _IMAGE_H_
#define _IMAGE_H_
class color
/*this is a virtual class for implementation convenience*/
{
public:
	virtual double magnitude()=0;
	/*Returns a double between 0 and 1
	indicating the "brighness" of the color.*/
};


class image
{
	list<list<color>>* data;
	int width;
	int height;
};
#endif