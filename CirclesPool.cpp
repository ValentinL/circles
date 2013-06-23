#include "CirclesPool.h"
#include <algorithm>
#include <functional>

template <>
void MoveObjects<Circle>(const std::tr1::shared_ptr< ObjectsPool<Circle> >& v,size_t scene_height,size_t scene_width)
{
	for(ObjectsPool<Circle>::iterator it=v->begin();it!=v->end();++it)
	{
		if( (it->getRadius()+it->getCenter().second)>scene_height)
			v->ResetObject(scene_width,scene_height,it);
		it->Move();
	}
}

