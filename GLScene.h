#ifndef _GL_SCENE_H
#define _GL_SCENE_H
#include <memory>
#include "GLFont.h"
#include "ShapesPool.h"
#include "shape.h"
#include "non_copyable.h"

class GLScene:private NonCopyable
{
private:
	size_t _w,_h;
	std::shared_ptr< GLFont > _font;				//font
	std::shared_ptr< ObjectsPool<Shape*> > v;		//our shapes


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