#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <cmath>
#include "constants.h"
#include "utils.h"
#include "shape.h"

class Circle:public Shape2D
{
private:
	float _r;			//circle radius
	point center;		//coord of center
	void init();
public:
	explicit Circle(float r,float x,float y,size_t numPoints=DefaultNumPoints,
											size_t Scores=DefaultScores,
											float Velocity=DefaultVelocity);

	point getCenter() const;	
	float getRadius() const; 
	virtual void Move(float x, float y, float z = 0);
	virtual void ResetShape(size_t w,size_t h);
	virtual bool PointInShape(const point& p) const;
	virtual bool ShapeInScreen(float width, float height) const;
};


class CircleFactory:public ShapeFactory
{
public:
	virtual std::shared_ptr<Shape> createShape(size_t w, size_t h)
	{
		size_t base = (w<h) ? w : h;
		float r = FloatRand(base / MinRadiusDelim, base / MaxRadiusDelim);
		return std::make_shared<Circle>(r, FloatRand(r, w - r), r);
	}
};

#endif