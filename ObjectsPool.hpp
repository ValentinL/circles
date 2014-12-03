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
class ObjectsPool :public _ObjectsPool<T>
{
};

//template function for move objects in pool
template <typename T>
void MoveObjects(std::shared_ptr<ObjectsPool<T>>& v,size_t scene_height,size_t scene_width);


#endif