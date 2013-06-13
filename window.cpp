#include "window.h"
#include <windows.h>
#include <tchar.h> 
#include <map>

bool cWindow::Create(
     HWND parent,				
     LPCWSTR text,				
     DWORD exstyle,DWORD style,	
     int x,int y,int w,int h,	
     UINT id
     )
   {
	 _hInstance=GetModuleHandle(0);
     
     WNDCLASSEX wndc;
     wndc.lpszClassName=L"MyWnd";
     wndc.cbSize=sizeof(WNDCLASSEX);
     wndc.lpfnWndProc=WNDPROC(_WndProc);
     wndc.cbClsExtra=0;
     wndc.cbWndExtra=0;
	 wndc.hbrBackground=HBRUSH(BLACK_PEN);
     wndc.hInstance=_hInstance;
     wndc.hCursor=LoadCursor(0,IDC_CROSS);
     wndc.style=CS_HREDRAW|CS_VREDRAW;
     wndc.hIcon=0;
     wndc.hIconSm=0;
     wndc.lpszMenuName=0;
     RegisterClassEx(&wndc);


	 //CreateWindow
     _hwnd=CreateWindowEx(exstyle,wndc.lpszClassName,text,
       style|WS_CLIPCHILDREN,
       x,y,w,h,parent,HMENU(id),
       _hInstance,
       this
       );

	changeSize();
    if(!_hwnd) return false;
    return true;
   }



LRESULT CALLBACK cWindow::_WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{  
	cWindow *wnd=0;

	if(message==WM_NCCREATE)
	{
		wnd=(cWindow*)LPCREATESTRUCT(lparam)->lpCreateParams;
		SetWindowLong(hwnd,GWL_USERDATA,LONG(LPCREATESTRUCT(lparam)->lpCreateParams));
		wnd->_hwnd=hwnd;      
	}

	wnd=(cWindow*)GetWindowLong(hwnd,GWL_USERDATA);

	if(wnd)
	{
		std::map<UINT,POINTER>::iterator it;
		it=wnd->_msgmap.find(message);

		if(it==wnd->_msgmap.end()) return DefWindowProc(hwnd,message,wparam,lparam);
		else
		{
			POINTER msg=it->second;        
			LRESULT result=(msg.wnd->*msg.func)(lparam,wparam);
			if(result) return result;
		}
	}
	return DefWindowProc(hwnd,message,wparam,lparam);
}

cWindow::~cWindow()
{
	if(!DestroyWindow(_hwnd)&&_hwnd)          
	{
	    _hwnd = NULL;							
	}

	if( !UnregisterClass( L"MyWnd", _hInstance ) )
	{
	    _hInstance = NULL;               
	}
	
};
 
