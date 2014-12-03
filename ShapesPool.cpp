#include "ShapesPool.h"
#include <algorithm>
#include <functional>

template <>
void MoveObjects<>(std::shared_ptr<ObjectsPool<Shape*>>& v,size_t scene_height,size_t scene_width)
{
	for(auto it= v->begin();it!=v->end();++it)
	{
		if ((*it)->ShapeInScreen(scene_width,scene_height))
			v->ResetObject(scene_width,scene_height,it);

		(*it)->Move(0,(*it)->getVelocity(),0);
	}
}


//function searches for the hit point in the circle
ObjectsPool<Shape*>::iterator
ShotInObject(const std::shared_ptr<ObjectsPool<Shape*>>& v, float x, float y)
{
	//find from end of vector, for  correct destroy shape
	//std::vector<T>::reverse_iterator it= std::find_if(v.get()->rbegin(),v.get()->rend(),
	//												std::tr1::bind(&InShape<T>, std::tr1::placeholders::_1,point(x,y)));
	auto it = std::find_if(v.get()->rbegin(), v.get()->rend(),
		std::bind2nd(std::mem_fun(&Shape::PointInShape), point(x, y)));

	if (it != v.get()->rend())
		return --it.base();
	else
		return v.get()->end();
}