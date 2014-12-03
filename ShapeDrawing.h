#ifndef _SHAPE_DRAWING_H_
#define _SHAPE_DRAWING_H_
#include <Windows.h>
#include <gl\gl.h>               
#include <gl\glu.h> 
#include "utils.h"

class ShapeDrawing
{
public:
	virtual void Draw(const float* first, const float* last, const color& c, float delta) const = 0;
	virtual ~ShapeDrawing(){};
};

class WinOpenGlDrawing1 :public ShapeDrawing
{
public:
	virtual void Draw(const float* first, const float* last, const color& c, float delta) const
	{
		glColor3f(c.r, c.g, c.b);
		glBegin(GL_TRIANGLE_FAN);
		do 
		{
			glVertex2f(*first, *(first+1) + delta);
			first+=2;
		} while (first != (last));
		
		glEnd();
	};
};
#endif