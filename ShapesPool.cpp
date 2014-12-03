#include "ShapesPool.h"
#include <algorithm>
#include <functional>

template <>
void MoveObjects<>(std::shared_ptr<ObjectsPool<shape_ptr>>& v, size_t scene_height, size_t scene_width)
{
	for(auto it= v->begin();it!=v->end();++it)
	{
		if ((*it)->ShapeInScreen(scene_width,scene_height))
			v->ResetObject(scene_width,scene_height,it);

		(*it)->Move(0,(*it)->getVelocity(),0);
	}
}

//function searches for the hit point in the circle
ObjectsPool<shape_ptr>::iterator
ShotInObject(const std::shared_ptr<ObjectsPool<shape_ptr>>& v, float x, float y)
{
	//find from end of vector, for  correct destroy shape
	auto it = std::find_if(v.get()->rbegin(), v.get()->rend(),
		std::bind(&Shape::PointInShape, std::placeholders::_1, point(x, y)));

	if (it != v.get()->rend())
		return --it.base();
	else
		return v.get()->end();
}