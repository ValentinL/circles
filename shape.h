#ifndef _SHAPE_H_
#define _SHAPE_H_
#include <vector>
#include "utils.h"
#include "constants.h"

//class represents a common part of shapes
class Shape
{
protected:

	size_t _numPoints;
	std::vector<float> points;
	color _c;
	float vel;
	size_t scores;
	float _DefaultVelocity;
	size_t _DefaultScores;
public:
	explicit Shape(size_t numPoints,size_t Scores=DefaultScores, size_t Velocity=DefaultVelocity);
	
	size_t getNumPoints() const;

	const float* getPoints() const;
	size_t getScores() const;
	const color& getColor() const;
	void Move();
	virtual ~Shape();
};

//general form of a predicate to search
//does not implement
//need to specialize for each type of shape
template <typename T>
bool InShape(const T& c, const point& p);


#endif