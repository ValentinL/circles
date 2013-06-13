#include "screen.h"
#include <windows.h>

Screen::Screen()
{
	HDC hDCScreen = GetDC(NULL);
	_width = GetDeviceCaps(hDCScreen, HORZRES);
	_height = GetDeviceCaps(hDCScreen, VERTRES);
	ReleaseDC(NULL, hDCScreen);
}

size_t Screen::getWidth() const
{
	return _width;
};

size_t Screen::getHeight() const
{
	return _height;
};
