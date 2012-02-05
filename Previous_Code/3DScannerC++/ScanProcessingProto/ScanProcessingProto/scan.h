#ifndef _SCAN_H_
#define _SCAN_H_

//dependancies
#include "list.h"
#include "image.h"
#include "pointcloud.h"
#include "hough.h"
#include "line.h"
#include "linear_combination.h"

list<Point2D>* BrightPoints(image* to_convert, double threshold)
{
	list<Point2D>* to_return=new list<Point2D>;
	for(int x=0; x<to_convert->Width(); x++)
		for(int y=0; y<to_convert->Height(); y++)
			if(to_convert->get(x,y).mag()>=threshold)
				to_return->add(new Point2D(x,y));
	return to_return;
}

class scan
{
private:
	image* background_image;
	list<image>* laser_images;
public:
	scan(char* filename)
	/*loads from a .scan file.
	This file type is a series of filenames. 
	The first is a background image
	the remaining lines are laser images*/
	{
		cout<<"Loading "<<filename<<"...\n";
		this->laser_images=new list<image>();
		ifstream myfile (filename);
		if (myfile.is_open())
		{
			int line_number=0;
			while (! myfile.eof() )
			{
				//load the line into a char[]
				string str;
				getline (myfile,str);

				char* line=new char[str.length()+1];
				for(int i=0; i<str.length(); i++)
					line[i]=str[i];
				line[str.length()]='\0';
				
				cout<<"	Loading "<<line<<"\n";

				if(line_number==0)
					background_image=LoadImage(line);
				else
					laser_images->add(LoadImage(line));
				line_number++;
			}
			myfile.close();
			cout<<filename<<" loaded.\n";
		}
		else
		{
			cout << "ERROR:Unable to open file "<<filename<<". Setting scan values to NULL.\n";
			this->background_image=NULL;
		}
	};
	void process(char* filename)
	/*turns the scan into an .obj file*/
	{
		pointcloud* cloud=new pointcloud();

		line* v= new line(1,0,30,1);
		line* u= new line(1,1,190,1);
		cout<<"Objects marked with \"*\" are incomplete.\n";
		for(int i=0; i<laser_images->size(); i++)
		{
			cout<<"Processing frame "<<i+1<<" of "<<laser_images->size()<<" ("<<100*(double)(i+1)/laser_images->size()<<"%)\n";
			
			image* Subtraction=SUBTRACT(this->laser_images->get(i), this->background_image);
			
			cout<<" Subtraction Done->";

			//WORK Clean/Threshold the data down to only the brightest points on the laser.
			image* Cleaned=Subtraction;
			
			cout<<" Cleaning Done*->";
			
			//Use Hough to find wall segments.
			HoughTransform* hough=new HoughTransform(5000,5000, Cleaned);
			//Extract the Basis.
			double threshold=255*2;//WORK thresholding or clustering should be dynamic....
			
			v= hough->GetLineNearest(v,2,threshold);
			v->print();
			u= hough->GetLineNearest(u,2,threshold);
			u->print();

			//the basis coordantes of the laser plane
			Point2D* unit_u=new Point2D(1/v->a(),-1/v->b());
			unit_u->Normalize();
			Point2D* unit_v=new Point2D(1/u->a(),-1/u->b());
			unit_v->Normalize();
			//the offset of the laser plane: use the x coord of intersection for now.
			double w_val=(u->b()-v->b())/(v->a()*u->b()-u->a()*v->b());
			
			cout<<" Basis Coordanates Obtained*->";
			
			//WORK Use coords to put points into the pointcloud.
			list<Point2D>* points=BrightPoints(Cleaned, 100);
			for(int j=0; j<points->size(); j++)
				cloud->add(new Point3D(Combine(unit_u, unit_v, points->get(j)), w_val));				
			
			cout<<" Frame Done\n";
		};
		cout<<"\nImage Processing Complete. Saving file "<<filename<<"...\n";
		SaveOBJ(cloud, filename);
		cout<<"Pointcloud saved.\n";
	};
};
#endif