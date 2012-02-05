#ifndef _LINEAR_COMBINATION_H_
#define _LINEAR_COMBINATION_H_

//dependancies
#include "point.h"

Point2D* Combine(Point2D* unit_u, Point2D* unit_v, Point2D* result)
/*returns (a,b) such that result=a*unit_u+b*unit_v*/
{
	return new Point2D(
		(result->y*unit_v->x-result->x*unit_v->y)/(unit_u->y*unit_v->x-unit_u->x*unit_v->y)
		,
		(result->y*unit_u->x-result->x*unit_u->y)/(unit_v->y*unit_u->x-unit_v->x*unit_u->y)
		);
};
#endif