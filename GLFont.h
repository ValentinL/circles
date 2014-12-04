#ifndef _GLFONT_H_
#define _GLFONT_H_
#include <windows.h>
#include <gl\gl.h>               
#include <gl\glu.h> 
class Font
{
public:
	virtual void BuildFont(HWND hwnd) = 0;
	virtual ~Font(){};
};

class GLFont:public Font
{
private:
	GLuint  base;      // font's base
public:
	void BuildFont(HWND hwnd); 
	void Release(GLvoid);
	void glPrint(const char *fmt, ...);
	~GLFont();
};


#endif