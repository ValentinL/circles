/*
some like a pool of objects
objects are not destroyed, 
and appear in a new location
*/

#ifndef _OBJECTS_POOL_HPP_
#define _OBJECTS_POOL_HPP_

#include "non_copyable.h"
#include <memory>
#include <vector>
#include <functional>
#include <algorithm>

//base part of pool
template <typename T>
class _ObjectsPool:private NonCopyable
{
protected:
	std::vector<T> v;
public:
	
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	typedef typename std::vector<T>::reverse_iterator reverse_iterator;
	typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;

	virtual void ResetObject(size_t w,size_t h,iterator it)=0;


	iterator begin()
	{
		return v.begin();
	}

	const_iterator begin() const
	{
		return v.begin();
	}

	iterator end()
	{
		return v.end();
	}

	const_iterator end() const
	{
		return v.end();
	}
	
	reverse_iterator rbegin()
	{
		return v.rbegin();
	}

	const_reverse_iterator rbegin() const
	{
		return v.rbegin();
	}

	reverse_iterator rend()
	{
		return v.rend();
	}

	const_reverse_iterator rend() const
	{
		return v.rend();
	}
	virtual ~_ObjectsPool(){};
};


//class for specialization
template <typename T>
class ObjectsPool:public _ObjectsPool<T>
{
};

//template function for move objects in pool
template <typename T>
void MoveObjects(const std::tr1::shared_ptr< ObjectsPool<T> >& v,size_t scene_height,size_t scene_width);

//function searches for the hit point in the circle
template <typename T>
typename ObjectsPool<T>::iterator 
ShotInObject(const std::tr1::shared_ptr< ObjectsPool<T> >& v,float x,float y)
{
	//find from end of vector, for  correct destroy shape
	std::vector<T>::reverse_iterator it= std::find_if(v.get()->rbegin(),v.get()->rend(),
													std::tr1::bind(&InShape<T>, std::tr1::placeholders::_1,point(x,y)));
	if(it!=v.get()->rend())
		return --it.base();
	else
		return v.get()->end();
}

#endif