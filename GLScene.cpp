#include "GLScene.h"
#include <gl\gl.h>               
#include <gl\glu.h> 

GLScene::GLScene(int NumObjects):TotalScore(0){}

int GLScene::Init( )                
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// set black color to clear screen

	v=boost::shared_ptr< ObjectsPool<Circle> >(new ObjectsPool<Circle>(_w,_h));	//make cirsles pool
	ReSizeGLScene(_w,_h);										
	return true;                
};


void GLScene::setFont( boost::shared_ptr<GLFont> font)	
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



void GLScene::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT );		//clear color buffer


	//draw objects
	for(ObjectsPool<Circle>::const_iterator it=v->begin();it!=v->end();++it)
	{

		glColor3f(it->getColor().r,it->getColor().g,it->getColor().b);
		glVertexPointer(2, GL_FLOAT, 0,  it->getPoints() );
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_TRIANGLE_FAN, 0, it->getNumPoints());
		glDisableClientState(GL_VERTEX_ARRAY);

		//glColor3f(it->getColor().r,it->getColor().g,it->getColor().b);
		//glBegin(GL_TRIANGLE_FAN);
		//	const float* p=it->getPoints(); 
		//	for(size_t i=0;i<it->getNumPoints()*2;i+=2)
		//		glVertex2f(p[i],p[i+1]);
		//glEnd();
	}

	MoveObjects(v,_h,_w);

	glColor3f(1,1,1);
	glRasterPos2f(0.0, _h);
	_font->glPrint("Scores: %d", TotalScore);  // Печать текста GL на экран
};

void GLScene::MouseClick(int MouseXPos,int MouseYPos)
{
	ObjectsPool<Circle>::iterator it=ShotInObject(v,MouseXPos,MouseYPos);
	
	if(it!=v->end())
	{
		TotalScore+=it->getScores();
		v->ResetObject(_w,_h,it);
	}
}
