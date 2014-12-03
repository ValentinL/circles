#include "circle.h"	


Circle::Circle(float r,float x,float y,size_t numPoints,size_t Scores,float Velocity):_r(r),center(x,y),Shape2D(numPoints,Scores,Velocity)
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

void Circle::ResetShape(size_t w, size_t h)
{
	size_t base = (w<h) ? w : h;
	float r = FloatRand(base / MinRadiusDelim, base / MaxRadiusDelim);
	_r = r;
	center.first = FloatRand(r, w - r);
	center.second = -r;
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

void Circle::Move(float x,float y,float z)
{
	Shape2D::Move(x,y,z);		//move all points
	center.first += x;
	center.second+= y;		//move center of circle
}

bool Circle::PointInShape(const point& p) const
{
	//if the distance between the center and point less than the radius
	//then point belongs to the circle
	float x = p.first - center.first;
	float y = p.second - center.second;

	float dist = std::sqrt(x*x + y*y);
	if (dist<_r)
		return true;

	return false;
}

bool Circle::ShapeInScreen(float width, float height) const
{
	if ((center.second - _r) > height) return true;
	return false;
}

