#include "shape.h"

float Shape::_DefaultVelocity = DefaultVelocity;
size_t Shape::_DefaultScores = DefaultScores;

Shape::Shape(size_t numPoints,size_t Scores,float Velocity):points(numPoints*2)
{};

float Shape::getVelocity() const
{	return vel;};

size_t Shape::getScores() const
{	return scores;	};

const color& Shape::getColor() const
{	return _c;		};

Shape::~Shape(){};

