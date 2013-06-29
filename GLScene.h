#ifndef _GL_SCENE_H
#define _GL_SCENE_H
#include <memory>
#include "GLFont.h"
#include "CirclesPool.h"
#include "non_copyable.h"

class GLScene:private NonCopyable
{
private:
	size_t _w,_h;
	std::tr1::shared_ptr<GLFont> _font;				//font
	std::tr1::shared_ptr< ObjectsPool<Circle> > v;		//our circles
	size_t TotalScore;								
public:

	GLScene(int NumObjects=DefaultNumObjects);

	int Init( );                

	void setFont( std::tr1::shared_ptr<GLFont> font);

	void ReSizeGLScene( GLsizei width,  GLsizei height  );        // change size 

	void Draw(float interpolation); 

	void Update();

	void MouseClick(float MouseXPos,float MouseYPos);
};

#endif