#ifndef _SCREEN_H_
#define _SCREEN_H_

//class represent Screen
class Screen
{
private:
	int _width,_height;
	Screen();
	Screen(const Screen& root);
	Screen& operator=(const Screen&);
public:
	static const Screen& getInstance()
	{
		 static Screen ScreenInstance;
         return ScreenInstance;
	}
	size_t getWidth() const;
	size_t getHeight() const;
};

#endif