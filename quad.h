#ifndef _QUAD_H_
#define _QUAD_H_
#include <cmath>
#include "constants.h"
#include "utils.h"
#include "shape.h"

class Quad:public Shape2D
{
private:
	float _angle;
	point _left, _right;
	void init();
public:
	explicit Quad(const point& left,const point& right, 
								size_t numPoints = 4,
								size_t Scores = DefaultScores,
								float Velocity = DefaultVelocity);

	virtual void Move(float x, float y, float z = 0);
	virtual void ResetShape(size_t w, size_t h);
	virtual bool PointInShape(const point& p) const;
	virtual bool ShapeInScreen(float width, float height) const;
};


class QuadFactory :public ShapeFactory
{
public:
	virtual std::shared_ptr<Shape> createShape(size_t w, size_t h)
	{
		size_t base = (w<h) ? w : h;
		float a = FloatRand(base / MinRadiusDelim, base / MaxRadiusDelim);
		float left = FloatRand(0, w);
		return std::make_shared<Quad>(point(left,-a),point( left+a,0));
	}
};

#endif