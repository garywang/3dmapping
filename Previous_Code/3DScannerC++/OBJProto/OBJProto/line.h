//THIS IS A STRIPPED DOWN LINE CLASS FOR PROTO PURPOSES.

#ifndef _LINE_H_
#define _LINE_H_

class line
{

	//a line of form ax+by=1
private:
	double _a;
	double _b;
public:
	double a(){return _a;};
	double b(){return _b;};
	line(double a, double b, double c)/*ax+by=c*/
	{
		_a=a/c;
		_b=b/c;
	}
};
#endif