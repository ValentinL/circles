#include "quad.h"	

Quad::Quad(const point& left, const point& right,
	size_t numPoints ,
	size_t Scores ,
	float Velocity ) :_left(left),_right(right),Shape2D(numPoints, Scores, Velocity)
{

	points[0] = left.first;
	points[1] = left.second;

	points[2] = right.first;
	points[3] = left.second;

	points[4] = right.first;
	points[5] = right.second;

	points[6] = left.first;
	points[7] = right.second;

	vel = _DefaultVelocity / (right.second-left.second);	//set velocity of circle
	scores = _DefaultScores / (right.second - left.second);	//set scores per circle
	_c.randomColor();
}

/*void Circle::init()
{
	float alpha = 0.0;
	float delta = 2 * PI / DefaultNumPoints;

	//set circle's points
	for (size_t i = 0; i<points.size(); i += 2, alpha += delta)
	{
		points[i] = center.first + _r*std::cos(alpha);
		points[i + 1] = center.second + _r*std::sin(alpha);
	}

	vel = _DefaultVelocity / _r;	//set velocity of circle
	scores = _DefaultScores / _r;	//set scores per circle
	_c.randomColor();

}*/

void Quad::ResetShape(float w, float h)
{
	size_t base = (w<h) ? w : h;
	float a = FloatRand(base / MinRadiusDelim, base / MaxRadiusDelim);
/*	_r = r;
	center.first = FloatRand(r, w - r);
	center.second = -r;
	init();*/
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


void Quad::Draw(float interpolation) const
{
	glColor3f(_c.r, _c.g, _c.b);
	glBegin(GL_TRIANGLE_FAN);
	float velocity = vel*interpolation;
	for (size_t i = 0; i < points.size(); i += 2)
		glVertex2f(points[i], points[i + 1] + velocity);
	glEnd();
}


bool Quad::ShapeInScreen(float width, float height) const
{
	if (_left.second > height) return true;
	return false;
}

//template <> bool ShapeInScreen<>(const Circle* s, float width, float height)
//{
//	if (((s->getCenter().second) - s->getRadius()) > height) return true;
//	return false;
//}
