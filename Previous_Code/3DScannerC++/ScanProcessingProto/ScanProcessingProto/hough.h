/************************
*     Original Code     *
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

#ifndef _HOUGH_H_
#define _HOUGH_H_

//dependancies
#include <math.h>
#include "cluster.h"
#include "line.h"
#include "list.h"
#include "image.h"
#include "macros.h"

class HoughTransform
{
private:
	double  _rho_max;  
	//rho varies from 0 to _rho_max=sqrt(width^2+height^2)
	//theta varies from 0 to 2*PI, so this data need not be stored.

	int    _rho_steps;	
	int    _theta_steps;

	double* _sin_cache;
	double* _cos_cache;

	double**  _hough_array;
	double    _mass;
public:
	HoughTransform(int rho_steps, int theta_steps, double rho_max)
	{
		_rho_steps=rho_steps;
		_theta_steps=theta_steps;
		_rho_max=rho_max;

		_sin_cache=new double[_theta_steps];
		_cos_cache=new double[_theta_steps];
		for(int step=0; step<_theta_steps; step++)
		{
			double theta=2*PI*step/_theta_steps;
			_sin_cache[step]=sin(theta);
			_cos_cache[step]=cos(theta);
		};

		_hough_array = new double*[_rho_steps];
		if (_hough_array != NULL) {
			for (int i = 0; i < _rho_steps; i++) {
				_hough_array[i] = new double[_theta_steps];
				for (int j = 0; j <_theta_steps; j++)
					_hough_array[i][j] = 0;
			}
		}	
		_mass=0;
	}
	HoughTransform(int rho_steps, int theta_steps, image* points)
	{
		_rho_steps=rho_steps;
		_theta_steps=theta_steps;
		_rho_max=points->Width()+points->Height();

		_sin_cache=new double[_theta_steps];
		_cos_cache=new double[_theta_steps];
		for(int step=0; step<_theta_steps; step++)
		{
			double theta=2*PI*step/_theta_steps;
			_sin_cache[step]=sin(theta);
			_cos_cache[step]=cos(theta);
		};

		_hough_array = new double*[_rho_steps];
		if (_hough_array != NULL) {
			for (int i = 0; i < _rho_steps; i++) {
				_hough_array[i] = new double[_theta_steps];
				for (int j = 0; j <_theta_steps; j++)
					_hough_array[i][j] = 0;
			}
		}	
		_mass=0;

		for(int x=0; x<points->Width(); x++)
			for(int y=0; y<points->Height(); y++)
				AddPoint(x,y,points->get(x,y).mag());
	};
	void AddPoint(double x, double y, double weight=1)
	{
		if(weight<=0)//Don't waste time on zero values, and don't allow negative values.
			return;
		//add this eqn to the accumulator...
		//rho=y*sin(theta)+x*cos(theta)
		for(int step=0; step<_theta_steps; step++)
		{
			double theta=2*PI*step/_theta_steps;
			double rho=y*_sin_cache[step]+x*_cos_cache[step];
			if(rho>0)//if rho<0, the created line will be addressed at theta(+/-)PI. Just ignore it
				_hough_array[int(rho*_rho_steps/_rho_max)][step]+=weight;
		}
		_mass+=weight;
	}
	void Print()
	{
		for (int i = 0; i <_rho_steps; i++)
		{
			for (int j = 0; j <_theta_steps; j++)
			{
				//Designed for debugging, not final use, so this should be single digit.
				cout<<_hough_array[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	line* GetBestLine()//Gets the best line in the accumulator.
	{
		int theta_step=0;
		double rho=0;
		double max=0;
		for (int i = 0; i < _rho_steps; i++) {
			for (int j = 0; j < _theta_steps; j++) {
				if(_hough_array[i][j]>max)
				{
					rho=i*_rho_max/_rho_steps;
					theta_step=j;
					max=_hough_array[i][j];
				}
			}
		}
		return new line(_cos_cache[theta_step],_sin_cache[theta_step],rho, 0);
	}
	list<line>* GetLines(double threshold_value)
	//Get all lines above a certian threshold. Quick, but tends to produce multiple lines near strong segments.
	{
		list<line>* Lines=new list<line>();
		for (int i = 0; i < _rho_steps; i++) {
			for (int j = 0; j < _theta_steps; j++) {
				if(_hough_array[i][j]>=threshold_value)
				{
					//Lines->add(new line(i*_rho_max/_rho_steps,j*2*PI/_theta_steps, _hough_array[i][j]));
					Lines->add(new line(_cos_cache[j],_sin_cache[j],i*_rho_max/_rho_steps,_hough_array[i][j]));
				}
			}
		}
		return Lines;
	}
	list<line>* GetNBestLines(int n, double threshold=2)
	{
		return (list<line>*)GetCenters(
			KMeans(			
				(list<datapoint>*) GetLines(threshold),
				n
				)
			);
	};
	line* GetLineNearest(line* start, int number_clusters, double threshold=2)
	{
		list<line>* end=this->GetNBestLines(number_clusters, threshold);
		double smallest_distance=-1;
		int smallest_index=0;
		for(int i=0; i<end->size(); i++)
		{
			double distance=start->distance(end->get(i));
			if(smallest_distance==-1||distance<smallest_distance)
			{
				smallest_distance=distance;
				smallest_index=i;
			}
		}
		return end->get(smallest_index);
	};
	void PrintCDF(int number_divisions)
	{
		int* CDF=new int[number_divisions];
		for(int i=0; i<number_divisions; i++)
			CDF[i]=0;
		for (int i = 0; i < _rho_steps; i++)
			for (int j = 0; j < _theta_steps; j++)
				for(int k=(_hough_array[i][j]/_mass)*number_divisions; k<number_divisions; k++)
					CDF[k]++;
		for(int i=0; i<number_divisions; i++)
		{
			cout<<"Threshold "<<(double)i/number_divisions<<": "<<((double)CDF[i])/(_rho_steps*_theta_steps)<<"\n";
			if(((double)CDF[i])/(_rho_steps*_theta_steps)==1)
				return;
		};
	};
	double Mass(){return _mass;};
};
#endif