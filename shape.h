#ifndef _SHAPE_H_
#define _SHAPE_H_
#include <vector>
#include <memory>
#include <map>
#include "utils.h"
#include "constants.h"
#include "ShapeDrawing.h"

//class represents a common part of shapes
class Shape
{
protected:
	std::vector<float> points;
	color _c;
	float vel;
	size_t scores;
	static float _DefaultVelocity;
	static size_t _DefaultScores;
public:
	explicit Shape(size_t numPoints,size_t Scores=DefaultScores, float Velocity=DefaultVelocity);
	float getVelocity() const;
	size_t getScores() const;
	const color& getColor() const;

	virtual bool PointInShape(const point& p) const = 0;
	virtual void Draw(ShapeDrawing* d, float interpolation) const = 0;
	virtual void Move(float x,float y,float z) = 0;
	virtual void ResetShape(size_t w, size_t h) = 0;
	virtual bool ShapeInScreen(float width, float height) const = 0;
	virtual ~Shape();
};

class Shape2D :public Shape
{
public:
	explicit Shape2D(size_t numPoints, size_t Scores = DefaultScores, float Velocity = DefaultVelocity):Shape(numPoints, Scores, Velocity){};

	virtual void Move(float x, float y, float z = 0)
	{
		for (size_t i = 0; i < points.size(); i += 2)
		{
			points[i + 1] += y;
			points[i] += x;
		}
	}

	void Draw(ShapeDrawing* d, float interpolation) const
	{
		float delta = vel*interpolation;
		d->Draw(&points[0], &points[0]+points.size() , _c, delta);
	}
};

class ShapeFactory
{
public:
	virtual Shape* createShape(size_t w, size_t h) = 0;
	virtual ~ShapeFactory() {}
};

//for easy create scene
class Registry
{
private:

	std::map<int, ShapeFactory*> Reg;
public:
	Shape* operator()(int number, int w, int h)
	{
		return Reg[number]->createShape(w, h);
	}

	void RegistryNew(ShapeFactory* f)
	{
		Reg.insert(std::make_pair(Reg.size(), f));
	}
};


#endif