#ifndef _SCREEN_H_
#define _SCREEN_H_

//class represent Screen
class Screen
{
private:
	int _width, _height;
	static Screen* _self;
	Screen();
	Screen(const Screen& root);
	Screen& operator=(const Screen&);
	virtual ~Screen(){}
public:
	static Screen* getInstance()
	{
		if (!_self)
			_self = new Screen();
		return _self;
	}

	static bool DeleteInstance()
	{
		if (_self)
		{
			delete _self;
			_self = 0;
			return true;
		}
		return false;
	}

	size_t getWidth() const;
	size_t getHeight() const;
};



#endif