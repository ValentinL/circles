#ifndef _UTILS_H_
#define _UTILS_H_
#include <utility>
#include <cstdlib>
#include <vector>
#include <memory>

typedef std::pair<float,float>			point;
typedef std::vector<point>				point_vector;
typedef std::vector<point>&				point_vector_ref;
typedef const std::vector<point>&		const_point_vector_ref;

struct color
{
	float r;
	float g;
	float b;
	void randomColor()
	{
		r=((float) rand() / (RAND_MAX));
		g=((float) rand() / (RAND_MAX));
		b=((float) rand() / (RAND_MAX));
	}
};

inline float FloatRand(float _max, float _min)
{ return _min + float(rand()) / RAND_MAX * (_max - _min); }

#endif