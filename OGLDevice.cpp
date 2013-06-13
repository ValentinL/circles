#include "OGLDevice.h"
#include <exception>
#include <gl\gl.h>               
#include <gl\glu.h> 


void OGLDevice::CreateDevice( HWND hWnd )
{
	PIXELFORMATDESCRIPTOR	pfd;
	memset( &pfd , 0 , sizeof( PIXELFORMATDESCRIPTOR ) );
	DEVMODE			devmode;
	memset( &devmode , 0 , sizeof( devmode ) );

	pfd.nSize		=	sizeof(PIXELFORMATDESCRIPTOR);
	
	pfd.nVersion		=	1;
	pfd.dwFlags		=	PFD_DRAW_TO_WINDOW | 
						PFD_SUPPORT_OPENGL | 
						PFD_DOUBLEBUFFER; 
	pfd.iPixelType	=	PFD_TYPE_RGBA;//rgba-color
	pfd.cColorBits	=	32;
	pfd.cDepthBits	=	32;
	pfd.iLayerType	=	PFD_MAIN_PLANE;
	
	int PixelFormat = ChoosePixelFormat( GetDC( hWnd ) , &pfd );

	if( PixelFormat == 0 )
	{
		PixelFormat = 1;
		//find pixel describe
		if( DescribePixelFormat( GetDC( hWnd ) , PixelFormat , sizeof( PIXELFORMATDESCRIPTOR ) , &pfd ) == 0 )
			throw std::exception("OpenGL: Can't find PixelFormat description");
	}

	//set pixel format
	if( SetPixelFormat( GetDC( hWnd ) , PixelFormat , &pfd  ) == NULL )
		throw std::exception("OpenGL: Can't set the PixelFormat");

	//make context
	if( ( hGLrc = wglCreateContext( GetDC( hWnd ) ) ) == NULL )
		throw std::exception("OpenGL: Can't create a GL Rendering Context");

	//make context current 
	if( wglMakeCurrent( GetDC( hWnd ) , hGLrc ) == false )
		throw std::exception("OpenGL: Can't Activate The GL Rendering Context");

	SetForegroundWindow( hWnd );
	SetFocus( hWnd );
}


void OGLDevice::SwapBuffers()
{
	::SwapBuffers( wglGetCurrentDC() );
}

void OGLDevice::Release()
{
	if( wglGetCurrentContext() != NULL )
		wglMakeCurrent( NULL , NULL );

	if( hGLrc != NULL )
	{
		wglDeleteContext( hGLrc );
		hGLrc = NULL;
	}
}

void OGLDevice::setVsync(bool enabled)
{
	PFNWGLSWAPINTERVALEXTPROC wglSwapInterval = NULL;
	wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
	if ( wglSwapInterval ) wglSwapInterval(enabled ? 1 : 0);
}	

OGLDevice::~OGLDevice()
{
	Release();
};