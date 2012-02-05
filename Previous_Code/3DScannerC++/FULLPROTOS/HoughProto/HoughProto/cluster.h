/************************
*     Original Code     *
*		  V 1.0			*
*   Will Oursler 2010   *
*ninjinuity.blogspot.com*
************************/

#ifndef _CLUSTER_H_
#define _CLUSTER_H_

//other code needed for this to work.
#include "list.h"

class datapoint
{
public:
	virtual double distance(datapoint* other) = 0;
	/*gives a distance between the two datapoints*/
	virtual datapoint* centroid(list<datapoint>* data) = 0;
	/*returns the centroid of the given datapoints*/
	/*The above really ought to be static, but I'm not sure how to work
	that (or that it's even possible). This method should NOT depend on
	which object is used to call it. It's a property of the type of object used.*/
};

typedef list<datapoint> cluster;

list<datapoint>* GetCenters(list<cluster>* Clusters)
{
	list<datapoint>* Centers=new list<datapoint>();
	for(int i=0; i<Clusters->size(); i++)
		Centers->add(Clusters->get(i)->get(0)->centroid(Clusters->get(i)));
	return Centers;
};

list<cluster>* KMeans(list<datapoint>* tocluster, int number_clusters)
/*returns at most number_clusters together containing all the datapoints.
Things to improve for V 1.1:
-Ensure that points are assigned randomly (or based of coords somehow,
while insuring clusters each have at least one point in them to start.
*/
{
	if(tocluster==NULL)
		return NULL;
	if(number_clusters<=1)
	/*No need to run the algorithm: there will be only one cluster.*/
	{
		list<cluster>* clusters=new list<cluster>();
		clusters->add(tocluster);
		return clusters;
	};

	if(number_clusters>tocluster->size())
	/*Make sure there will be at least one point to a cluster*/
	{
		number_clusters=tocluster->size();
	};

	list<cluster>* clusters=new list<cluster>();
	for(int i=0; i<number_clusters; i++)//Initialize clusters
		clusters->add(new cluster());
	for(int i=0; i<tocluster->size(); i++)//Add the points to clusters. Make sure at least one point is each cluster.
		(clusters->get(i%number_clusters))->add(tocluster->get(i));
	
	bool SteadyState;
	do{
		SteadyState=true;//Assume steady state until something moves;
		list<datapoint>* centroids=new list<datapoint>();
		list<cluster>* temp_clusters=new list<list<datapoint>>();
		for(int i=0; i<clusters->size(); i++){//init lists
			centroids->add(clusters->get(i)->get(0)/*sloppy, I know, but it'll work*/->centroid(clusters->get(i)));
			temp_clusters->add(new cluster());
		}
		//for each cluster
		for(int i=0; i<clusters->size(); i++)
		{
			for(int j=0; j<clusters->get(i)->size(); j++)
			{
				datapoint* data=clusters->get(i)->get(j);
				//find the index of the cluster with minimum distance
				int min_index=-1;
				double min_distance=-1;
				for(int k=0; k<centroids->size(); k++)
				{
					if((min_distance==-1)||(data->distance(centroids->get(k))<min_distance))
					{
						min_index=k;
						min_distance=data->distance(centroids->get(k));
					};
				};
				if(min_index!=i)//point is being reassigned
					SteadyState=false;
				temp_clusters->get(min_index)->add(data);
			};
		};
		//check if any index in temp clusters is empty
		for(int i=0; i<temp_clusters->size(); i++)
		{
			if(temp_clusters->get(i)->size()==0)
			/*if this happens, then there's an empty cluster. Remove it.*/
			{
				temp_clusters->remove(i);
				i=i-1;//recheck this index...
			};
		};
		delete clusters;
		clusters=temp_clusters;
	}while(!SteadyState);
	return clusters;
};

#endif