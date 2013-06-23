#include <ctime>
#include <memory>

#include "screen.h"
#include "constants.h"

#include "winApplication.h"
#include "window.h"
#include "OGLDevice.h"
#include "GLFont.h"
#include "GLScene.h"
#include "non_copyable.h"

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")

//our GLWindow class
class myGLWindow: private NonCopyable,public cWindow
{
private:
	std::tr1::shared_ptr<GLScene> _scene;	
	bool isActive;						//window activity flag
public:
	myGLWindow()
	{
		//register messages and handlers
		AddMessage(WM_DESTROY,this,&myGLWindow::OnDestroy);
		AddMessage(WM_SIZE,this,&myGLWindow::OnResize);
		AddMessage(WM_TIMER,this,&myGLWindow::OnTimer);
		AddMessage(WM_LBUTTONDOWN,this,&myGLWindow::OnMouseClick);
		AddMessage(WM_ACTIVATE,this,&myGLWindow::OnActivate);
	}

	void setScene(std::tr1::shared_ptr<GLScene> scene)
	{
		_scene=scene;
	}

	LRESULT OnActivate(LPARAM lparam,WPARAM wparam)
	{
		if( !HIWORD( wparam ) )       //check minimize state
			isActive = true;          
		else
			isActive = false;         
		return 0;						
	}

	LRESULT OnDestroy(LPARAM lparam,WPARAM wparam)
	{
		PostQuitMessage(0);
		return 0;
	}


	LRESULT OnResize(LPARAM lparam,WPARAM wparam)
	{
		this->changeSize();										//change window size
		_scene->ReSizeGLScene(LOWORD(lparam), HIWORD(lparam));	//resize
		return 0;
	}
   

	LRESULT OnTimer(LPARAM lparam,WPARAM wparam)
	{
		if(isActive)					//if program is active
		{
			_scene->Draw();				//draw a picture
			OGLDevice::SwapBuffers();
		}
		return 0;
	}

	LRESULT OnMouseClick(LPARAM lparam,WPARAM wparam)
	{
		_scene->MouseClick(LOWORD(lparam),HIWORD(lparam));
		return 0;
	}

	~myGLWindow()	{};
 };



int APIENTRY WinMain(HINSTANCE hinst,HINSTANCE prev,LPSTR cmd,int showcmd)
 {

	srand(time(NULL));				//set random number generator					
	std::tr1::shared_ptr<myGLWindow>	wnd(new myGLWindow);	//window
	std::tr1::shared_ptr<OGLDevice>	Device(new OGLDevice);	//openGL device
	std::tr1::shared_ptr<GLScene>		scene(new GLScene);		//openGL scene
	std::tr1::shared_ptr<GLFont>		font(new GLFont);		

	
	try
	{
		wnd->setScene(scene);		//set scene into window
									//create window
		
		wnd->Create(0,L"Circles",0,WS_OVERLAPPEDWINDOW|WS_VISIBLE,Screen::getInstance().getWidth()/8,
																  Screen::getInstance().getHeight()/8,
																  Screen::getInstance().getWidth()*0.75,
																  Screen::getInstance().getHeight()*0.75,0);
		
		Device->CreateDevice( wnd->getHandle() );				//set openGL device into window
		Device->setVsync(false);					//off V-sync

		scene->setFont(font);						//set font into scene
		font->BuildFont(wnd->getHandle());			

		scene->Init();							

		SetTimer(wnd->getHandle(),1,17,NULL);		
		
		std::tr1::shared_ptr<WinApplication> app(new WinApplication); 		//run appliction
		app->Run();
		
	}
	catch(std::exception& ex)
	{
		MessageBoxA( 0, ex.what(), "Error", MB_OK | MB_ICONEXCLAMATION); 
	}
	catch(...)
	{
		MessageBoxA( 0, "Uncatched exception", "Error", MB_OK | MB_ICONEXCLAMATION); 
	}
	return 0;
 }
