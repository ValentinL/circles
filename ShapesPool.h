#ifndef _SHAPES_POOL_H_
#define _SHAPES_POOL_H_
#include <memory>
#include "ObjectsPool.hpp"
#include "Shape.h"
#include "Circle.h"
#include "Quad.h"

//specialization for object's pool 
//for Circle
//
template <>
class ObjectsPool<Shape*>:public _ObjectsPool<Shape*>
{
public:

	//make a pool of Shapes
	explicit ObjectsPool(size_t w,size_t h,size_t NumObjects=DefaultNumObjects)
	{
		CircleFactory* circle_factory = new  CircleFactory();
		QuadFactory*   quad_factory   = new  QuadFactory();
		for(size_t i=0;i<NumObjects;i++)
		{
			size_t base=(w<h)?w:h;
			float r=FloatRand(base/MinRadiusDelim,base/MaxRadiusDelim);
			if (i%2)
				v.push_back(circle_factory->createShape(w,h));
			else
				v.push_back(quad_factory->createShape(w,h));
		}

	};

	//do not remove the object, but simply give the new coordinates
	void ResetObject( size_t w,size_t h,ObjectsPool<Shape*>::iterator it )
	{
		(*it)->ResetShape(w, h);
	};
};


template <>
void MoveObjects<>(std::shared_ptr<ObjectsPool<Shape*>>& v, size_t scene_height, size_t scene_width);

//function searches for the hit point in the circle
ObjectsPool<Shape*>::iterator
ShotInObject(const std::shared_ptr<ObjectsPool<Shape*>>& v, float x, float y);

#endif
