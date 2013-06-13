#ifndef _GL_SCENE_H
#define _GL_SCENE_H
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include "GLFont.h"
#include "CirclesPool.h"

class GLScene:private boost::noncopyable			
{
private:
	size_t _w,_h;
	boost::shared_ptr<GLFont> _font;				//font
	boost::shared_ptr< ObjectsPool<Circle> > v;		//our circles
	size_t TotalScore;								
public:

	GLScene(int NumObjects=DefaultNumObjects);

	int Init( );                

	void setFont( boost::shared_ptr<GLFont> font);

	void ReSizeGLScene( GLsizei width,  GLsizei height  );        // change size 

	void Draw(); 

	void MouseClick(int MouseXPos,int MouseYPos);
};

#endif