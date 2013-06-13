#include "winApplication.h"
#include <windows.h>

void WinApplication::Run()
{
	MSG msg;
	while(GetMessage(&msg,0,0,0)!=0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}    
}