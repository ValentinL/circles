#ifndef _CIRCLES_POOL_H_
#define _CIRCLES_POOL_H_
#include <memory>
#include "ObjectsPool.hpp"
#include "Circle.h"


//specialization for object's pool 
//for Circle

template <>
class ObjectsPool<Circle>:public _ObjectsPool<Circle>
{
public:

	//make a pool of Circles
	explicit ObjectsPool(size_t w,size_t h,size_t NumObjects=DefaultNumObjects)
	{
		for(size_t i=0;i<NumObjects;i++)
		{
			size_t base=(w<h)?w:h;
			float r=FloatRand(base/MinRadiusDelim,base/MaxRadiusDelim);
			v.push_back(Circle(r,FloatRand(r,w-r),r));
		}
	};

	//do not remove the object, but simply give the new coordinates
	void ResetObject( size_t w,size_t h,ObjectsPool<Circle>::iterator it )
	{
		size_t base=(w<h)?w:h;
		float r=FloatRand(base/MinRadiusDelim,base/MaxRadiusDelim);
		it->setCircle(r,FloatRand(r,w-r),r);
	};
};


template <>
void MoveObjects<Circle>(const std::tr1::shared_ptr< ObjectsPool<Circle> >& v,size_t scene_height,size_t scene_width);


#endif