#include "shape.h"


Shape::Shape(size_t numPoints,size_t Scores,float Velocity):_numPoints(numPoints),_DefaultScores(Scores),_DefaultVelocity(Velocity),points(_numPoints*2)
{};

size_t Shape::getNumPoints() const
{	return _numPoints;	};


const float* Shape::getPoints() const
{	
	//can use vector::data(), but not in my compiler
	return &points[0];	
};

size_t Shape::getScores() const
{	return scores;	};

const color& Shape::getColor() const
{	return _c;		};

void Shape::Move()
{	
	for(size_t i=0;i<points.size();i+=2)
		points[i+1]+=vel;
}

Shape::~Shape(){};

//so slow
//void Shape::Move()
//{	
//	for(point_vector::iterator it=points.begin();it!=points.end();++it)
//		it->second+=vel;
//}