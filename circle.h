#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <cmath>
#include "constants.h"
#include "utils.h"
#include "shape.h"

class Circle:public Shape
{
private:
	float _r;			//circle radius
	point center;		//coord of center
	void init();
public:
	explicit Circle(float r,float x,float y,size_t numPoints=DefaultNumPoints,
											size_t Scores=DefaultScores,
											float Velocity=DefaultVelocity);

	//generates new parameters for the circle
	void setCircle(float r,float x,float y,size_t numPoints=DefaultNumPoints);
	point getCenter() const;	
	float getRadius() const;

	//move circle down
	void Move();
};


//specialization of function template InShape
//determines whether the point of the circle
template <>
bool InShape<Circle>(const Circle& c, const point& p);

#endif