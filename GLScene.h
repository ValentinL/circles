#ifndef _GL_SCENE_H
#define _GL_SCENE_H
#include <memory>
#include "GLFont.h"
#include "ShapesPool.h"
#include "ShapeDrawing.h"
#include "shape.h"
#include "non_copyable.h"

//base Scene
class Scene
{
protected:
	size_t _w, _h;
	size_t TotalScore;
public:
	Scene():TotalScore(0){};
	virtual int Init() = 0;
	virtual void setFont(const std::shared_ptr<Font>& font) = 0;
	virtual void ReSizeScene(int width, int height) = 0;        // change size 
	
	virtual void Draw(float interpolation) = 0;
	virtual void Update() = 0;
	virtual void MouseClick(float MouseXPos, float MouseYPos) = 0;

};

//OpenGL Scene
template <typename T = ObjectsPool<std::shared_ptr<Shape>> >
class GLScene:public Scene,private NonCopyable
{
private:
	std::shared_ptr< GLFont > _font;	//font
	std::shared_ptr< T >  v;			//our shapes
public:

	GLScene(int NumObjects=DefaultNumObjects);
	int Init();                

	void setFont(const std::shared_ptr<Font>& font);
	void ReSizeScene(int width, int height);        // change size 

	void Draw(float interpolation); 
	void Update();
	void MouseClick(float MouseXPos,float MouseYPos);
};


template <typename T> GLScene<T>::GLScene(int NumObjects):Scene(){}

template <typename T>
int GLScene<T>::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// set black color to clear screen
	v = std::make_shared<T>(_w, _h);	//make cirsles pool
	ReSizeScene(_w, _h);
	return true;
};

template <typename T>
void GLScene<T>::setFont(const std::shared_ptr<Font>& font)
{
	_font = std::dynamic_pointer_cast<GLFont>(font);
};

template <typename T>
void GLScene<T>::ReSizeScene(int width, int height)        // change size and init GL
{

	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);			// set viewport

	glMatrixMode(GL_PROJECTION);				// get projection matrix
	glLoadIdentity();							// reset projection matrix
	gluOrtho2D(0, width, height, 0);				// projection
	glMatrixMode(GL_MODELVIEW);				// get model view matix
	glLoadIdentity();							// reset model view matrix

	_w = width;
	_h = height;

}

template <typename T>
void GLScene<T>::Draw(float interpolation)
{
	glClear(GL_COLOR_BUFFER_BIT);		//clear color buffer
	//draw objects
	auto drawer = std::make_shared<WinOpenGlDrawing1>();
	for (auto it = v->begin(); it != v->end(); ++it)
		(*it)->Draw(drawer, interpolation);

	glColor3f(1, 1, 1);
	glRasterPos2f(0.0, (GLfloat)_h);
	_font->glPrint("Scores: %d", TotalScore);  // print text
};

template <typename T>
void GLScene<T>::Update()
{
	MoveObjects(v, _h, _w);
};

template <typename T>
void GLScene<T>::MouseClick(float MouseXPos, float MouseYPos)
{
	auto it = ShotInObject(v, MouseXPos, MouseYPos);

	if (it != v->end())
	{
		TotalScore += (*it)->getScores();
		v->ResetObject(_w, _h, it);
	}
}


#endif