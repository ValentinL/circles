#include "circle.h"	

Circle::Circle(float r,float x,float y,size_t numPoints,size_t Scores,float Velocity):_r(r),center(x,y),Shape(numPoints,Scores,Velocity)
{
	init();
}
	
void Circle::init()
{
	float alpha=0.0;
	float delta=2*PI/DefaultNumPoints;
	
	//set circle's points
	for(size_t i=0;i<points.size();i+=2,alpha+=delta)
	{
		points[i]	=center.first+_r*std::cos(alpha);
		points[i+1] =center.second+_r*std::sin(alpha);
	}

	vel=_DefaultVelocity/_r;	//set velocity of circle
	scores=_DefaultScores/_r;	//set scores per circle
	_c.randomColor();

}

void Circle::setCircle(float r,float x,float y,size_t numPoints)
{
	_r=r;
	center.first=x;
	center.second=y;
	init();
}

point Circle::getCenter() const
{
	return center;
}

float Circle::getRadius() const
{
	return _r;
}

void Circle::Move()
{
	Shape::Move();		//move all points
	center.second+=vel;	//move center of circle
}


template <>
bool InShape<Circle>(const Circle& c, const point& p)
{
	//if the distance between the center and point less than the radius
	//then point belongs to the circle
	float x=p.first-c.getCenter().first;
	float y=p.second-c.getCenter().second;

	float dist=std::sqrt(x*x+y*y);
	if(dist<c.getRadius())
		return true;

	return false;
}

