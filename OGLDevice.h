#ifndef _OGLDEVICE_H_
#define _OGLDEVICE_H_
#include <windows.h>
class RenderDevice{ };

class	OGLDevice:public RenderDevice
{
	//OpenGL context
	HGLRC hGLrc;
	typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
public:
	void CreateDevice( HWND hWnd );
	void Release( void );
	static void SwapBuffers( void );

	void setVsync(bool enabled); // true -- VSync on, false -- off

	~OGLDevice();
};


#endif