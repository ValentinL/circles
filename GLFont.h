#ifndef _GLFONT_H_
#define _GLFONT_H_
#include <windows.h>
#include <gl\gl.h>               
#include <gl\glu.h> 

class GLFont
{
private:
	GLuint  base;      // font's base
public:
	GLvoid BuildFont(HWND hwnd); 
	GLvoid Release(GLvoid);
	GLvoid glPrint(const char *fmt, ...);
	~GLFont();
};


#endif