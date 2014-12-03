#ifndef _SHAPES_POOL_H_
#define _SHAPES_POOL_H_
#include <memory>
#include "ObjectsPool.hpp"
#include "Circle.h"
#include "Quad.h"
#include <map>
//specialization object's pool for Shape*
//typedef Shape* shape_ptr;
typedef std::shared_ptr<Shape> shape_ptr;

template <>
class ObjectsPool<shape_ptr>:public _ObjectsPool<shape_ptr>
{
public:

	//make a pool of Shapes
	explicit ObjectsPool(size_t w,size_t h,size_t NumObjects=DefaultNumObjects)
	{
		Registry reg;
		reg.RegistryNew(std::make_shared<CircleFactory>());
		reg.RegistryNew(std::make_shared<QuadFactory>());
		for(size_t i=0;i<NumObjects;i++)
		{
			size_t base=(w<h)?w:h;
			float r=FloatRand(base/MinRadiusDelim,base/MaxRadiusDelim);
			v.push_back(reg(i % 2, w, h));
		}

	};

	//do not remove the object, but simply give the new coordinates
	void ResetObject(size_t w, size_t h, ObjectsPool<shape_ptr>::iterator it)
	{
		(*it)->ResetShape(w, h);
	};
};


template <>
void MoveObjects<>(std::shared_ptr<ObjectsPool<shape_ptr>>& v, size_t scene_height, size_t scene_width);

//function searches for the hit point in the circle
ObjectsPool<shape_ptr>::iterator
ShotInObject(const std::shared_ptr<ObjectsPool<shape_ptr>>& v, float x, float y);

#endif
