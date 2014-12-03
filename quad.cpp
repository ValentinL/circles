#include "quad.h"	

Quad::Quad(const point& left, const point& right,
			size_t numPoints ,
			size_t Scores ,
			float Velocity ) :_left(left),_right(right),Shape2D(numPoints, Scores, Velocity)
{

	init();
}

void Quad::init()
{
	points[0] = _left.first;
	points[1] = _left.second;

	points[2] = _right.first;
	points[3] = _left.second;

	points[4] = _right.first;
	points[5] = _right.second;

	points[6] = _left.first;
	points[7] = _right.second;

	vel = _DefaultVelocity / (float) (_right.second - _left.second);	//set velocity of circle
	scores = _DefaultScores / (size_t) (_right.second - _left.second);	//set scores per circle
	_c.randomColor();
}

void Quad::ResetShape(size_t w, size_t h)
{
	size_t base = (w<h) ? w : h;
	float a = FloatRand(base / MinRadiusDelim, base / MaxRadiusDelim);
	float left = FloatRand(0, (float) w);
	_left = point(left, -a);
	_right = point(left + a, 0);
	init();
}


void Quad::Move(float x, float y, float z)
{
	Shape2D::Move(x, y, z);		//move all points
}

bool Quad::PointInShape(const point& p) const
{
	//if the distance between the center and point less than the radius
	//then point belongs to the circle
	
	if ((p.first >= points[0] && p.first <= points[4]) &&
		(p.second >= points[1] && p.second <= points[5]))
		return true;
	return false;
}

bool Quad::ShapeInScreen(float width, float height) const
{
	if (points[1] > height) return true;
	return false;
}
