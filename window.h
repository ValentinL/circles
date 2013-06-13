#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <tchar.h> 
#include <map>

class cWindow
{
private:
   typedef LRESULT (cWindow::*FuncPointer)(LPARAM,WPARAM);

   struct POINTER
   {
     cWindow* wnd;
     FuncPointer func;
   };

protected:
  
	std::map<UINT,POINTER> _msgmap;//message map

	static LRESULT CALLBACK _WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam);
 
	template<typename T>
	bool AddMessage(UINT message,cWindow* wnd,LRESULT (T::*funcpointer)(LPARAM,WPARAM));

	void changeSize()
	{
		RECT rect;
		GetClientRect(_hwnd, &rect);
		_width = rect.right;
		_height = rect.bottom;
	}

	HWND _hwnd;
	HINSTANCE _hInstance;
	int _width,_height;

 public:

	bool Create(
		HWND parent,				//Parent window, if 0 then main window
		LPCWSTR text,				//window caption
		DWORD exstyle,DWORD style,	//window style's
		int x,int y,int w,int h,	//left,upper,width,height
		UINT id						
		);
	HWND getHandle(){return _hwnd;};
	int	 getWidth(){return _width;};
	int  getHeight(){return _height;};
	virtual ~cWindow();
};

template<typename T>
bool cWindow::AddMessage(UINT message,cWindow* wnd,LRESULT (T::*funcpointer)(LPARAM,WPARAM))
{
	if(!wnd || !funcpointer) return false;

	POINTER msg;
	msg.wnd=wnd;
	
	msg.func=static_cast<FuncPointer>(funcpointer);

	_msgmap.insert(std::pair<UINT,POINTER>(message,msg));

	return true;
};
#endif