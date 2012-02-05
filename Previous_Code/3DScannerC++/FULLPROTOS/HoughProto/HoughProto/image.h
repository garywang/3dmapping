#ifndef _IMAGE_H_
#define _IMAGE_H_

//dependancies
#include "color.h"
#include "macros.h"
#include <fstream>
#include <string>

class image{
private:
	color** data;
	int width;
	int height;
public:
	image(int Width, int Height)
	{
		width=Width;
		height=Height;

		this->data=new color*[width];
		for(int x=0; x<width; x++)
		{
			this->data[x]=new color[height];
			for(int y=0; y<height; y++)
				this->data[x][y]=color(0,0,0);
		};
	};
	image(int Width, int Height, color DEFAULT)
	{
		width=Width;
		height=Height;

		this->data=new color*[width];
		for(int x=0; x<width; x++)
		{
			this->data[x]=new color[height];
			for(int y=0; y<height; y++)
				this->data[x][y]=DEFAULT;
		};
	};
	int Width(){return width;};
	int Height(){return height;};
	color get(int x, int y)
	{
		return this->data[x][y];
	};
	void set(int x, int y, color c)
	{
		this->data[x][y]=c;
	};
	void print()
	{
		for(int x=0; x<height; x++)
		{
			for(int y=0; y<width ; y++)
				this->data[y][x].print();
			cout<<'\n';
		};
	};
};

image* SUBTRACT(image* A, image* B)
{
	int width=MIN(A->Width(),B->Width());
	int height=MIN(A->Height(),B->Height());
	image* diffrence=new image(width, height);
	for(int x=0; x<width; x++)
		for(int y=0; y<height; y++)
			diffrence->set(x,y,SUBTRACT(A->get(x,y),B->get(x,y)));
	return diffrence;
};

image* LoadImage(char* filename)
{
	image* IMAGE=NULL;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		int line_number=0;
		int X=0;
		int Y=0;
		int R=0;
		int G=0;
		int B=0;
		int A=0;
		while (! myfile.eof() )
		{
			//load the line into a char[]
			string str;
			getline (myfile,str);

			char* line=new char[str.length()+1];
			for(int i=0; i<str.length(); i++)
				line[i]=str[i];
			line[str.length()]='\0';
			
			int token_number=0;
			char *p = strtok(line, " ");
			while (p) {
				//cout<<"Token #("<<line_number<<","<<token_number<<")="<<(int)atof(p)<<"\n";
				//figure out to what the token belongs and assign it.
				if(line_number%2==0)//this is an X Y line
				{
					if(token_number==0)
						X=(int)atof(p);
					else
						Y=(int)atof(p);
				}
				else//This is an RGBA line
				{
					if(token_number==0)
						R=(int)atof(p);
					else if(token_number==1)
						G=(int)atof(p);
					else if(token_number==2)
						B=(int)atof(p);
					else
						A=(int)atof(p);
				}
				p = strtok(NULL, " ");
				if(line_number==1)//Image specs loaded.
					IMAGE=new image(X,Y, color(R,G,B,A));
				else if(line_number%2==1)//pixel data should be loaded. Use it.
					IMAGE->set(X,Y, color(R,G,B,A));
				token_number++;
			}
			line_number++;
		}
		myfile.close();
	}
	else cout << "ERROR:Unable to open file "<<filename<<"\n";
	return IMAGE;
};

void SaveImage(image* tosave, char* filename)
{
	ofstream imagefile;
	imagefile.open (filename);
	imagefile<<tosave->Width()<<" "<<tosave->Height()<<"\n";
	imagefile<<"0 0 0 0\n";
	for(int x=0; x<tosave->Width(); x++)
		for(int y=0; y<tosave->Height(); y++)
		{
			color c=tosave->get(x,y);
			if(c.r+c.g+c.b>0)
			{
				imagefile<<x<<" "<<y<<"\n";
				imagefile<<c.r<<" "<<c.g<<" "<<c.b<<" "<<c.a<<"\n";
			}
		};
	imagefile.close();
};
#endif