#include "GLScene.h"
#include <gl\gl.h>               
#include <gl\glu.h> 
#include "ShapeDrawing.h"

GLScene::GLScene(int NumObjects):TotalScore(0){}

int GLScene::Init( )                
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// set black color to clear screen

	//v=std::tr1::shared_ptr< ObjectsPool<Circle> >(new ObjectsPool<Circle>(_w,_h));	//make cirsles pool
	v = std::shared_ptr< ObjectsPool<Shape*> >(new ObjectsPool<Shape*>(_w, _h));	//make cirsles pool


	ReSizeGLScene(_w,_h);										
	return true;                
};


void GLScene::setFont( std::tr1::shared_ptr<GLFont> font)	
{
	_font=font;
};

void GLScene::ReSizeGLScene(  GLsizei width,  GLsizei height )        // change size and init GL
{

	if( height == 0 )							
		height = 1;

	glViewport( 0, 0, width, height );			// set viewport

	glMatrixMode( GL_PROJECTION );				// get projection matrix
	glLoadIdentity();							// reset projection matrix
	gluOrtho2D(0,width, height,0);				// projection
	glMatrixMode( GL_MODELVIEW );				// get model view matix
	glLoadIdentity();							// reset model view matrix

	_w=width;		
	_h=height;

}



void GLScene::Draw(float interpolation)
{
	glClear( GL_COLOR_BUFFER_BIT );		//clear color buffer

	//draw objects
	auto drawer = new WinOpenGlDrawing1();
	for(ObjectsPool<Shape*>::const_iterator it=v->begin();it!=v->end();++it)
	{
		(*it)->Draw (drawer, interpolation);
	}

	glColor3f(1,1,1);
	glRasterPos2f(0.0, (GLfloat)_h);
	_font->glPrint("Scores: %d", TotalScore);  // Печать текста GL на экран
};

void GLScene::Update()
{
	
	MoveObjects(v,_h,_w);
};

void GLScene::MouseClick(float MouseXPos,float MouseYPos)
{
	auto it=ShotInObject(v,MouseXPos,MouseYPos);
	
	if ( it != v->end())
	{
		TotalScore += (*it)->getScores();
		v->ResetObject(_w, _h, it);
	}
}
