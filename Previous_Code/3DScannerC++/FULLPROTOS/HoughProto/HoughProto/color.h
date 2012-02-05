#ifndef _COLOR_H_
#define _COLOR_H_
struct color{
	int r;
	int g;
	int b;
	int a;
	color(){color(0,0,0,0);};
	color(int mag)//makes a grey color
	{
		r=mag;
		g=mag;
		b=mag;
		a=255;
	};
	color(int R, int G, int B)
	{
		r=R;
		g=G;
		b=B;
		a=255;
	};
	color(int R, int G, int B, int A)
	{
		r=R;
		g=G;
		b=B;
		a=A;
	};
	double mag()
	{
		return ((double)(r+g+b)*a)/(3*255);
	};
	void print()
	{
		int mag=((r+g+b)*a)/(3*255);
		if(mag<51)
			cout<<'.';
		else if(mag<102)
			cout<<'o';
		else if(mag<153)
			cout<<'=';
		else if(mag<204)
			cout<<'#';
		else
			cout<<'@';
	};
};

/*Define some constants and functions to make code more readable*/
const color BLANK=color(0,	0,	0,	0	);
const color BLACK=color(0,0,0);
const color WHITE=color(255,255,255	);
color GREY(int x){return color(x);};

color SUBTRACT(color A, color B)
/*works best when both colors have similar opacities. Not sure how to deal with thin colors...*/
{
	return color(
		((A.r>B.r) ? A.r-B.r : 0),
		((A.g>B.g) ? A.g-B.g : 0),
		((A.b>B.b) ? A.b-B.b : 0),
		(A.a+B.a)/2
		);
};
#endif