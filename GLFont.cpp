#include "GLFont.h"
#include <cstdio>
#include <cstdarg>

GLvoid GLFont::BuildFont(HWND hwnd)  
{
	HFONT  font;            
	base = glGenLists(96);  
	font = CreateFont(  25,        // font's height
	0,							
	0,        
	0,        
	FW_BOLD,     
	FALSE,       
	FALSE,       
	FALSE,       
	ANSI_CHARSET,  
	OUT_TT_PRECIS,  
	CLIP_DEFAULT_PRECIS,    
	ANTIALIASED_QUALITY,    
	FF_DONTCARE|DEFAULT_PITCH, 
	L"Courier New");				// font's name
  	SelectObject(GetDC( hwnd ), font);       
	wglUseFontBitmaps(GetDC( hwnd ), 32, 96, base); 
}

GLvoid GLFont::Release(GLvoid)            
{
	glDeleteLists(base, 96);        
}

GLvoid GLFont::glPrint(const char *fmt, ...)        //print phrase in fmt 
{
	char    text[256];      
	va_list    ap;          
	if (fmt == NULL)		// text is empty
		return;				
	va_start(ap, fmt);      //parse string
	vsprintf(text, fmt, ap); 
	va_end(ap);              
	glPushAttrib(GL_LIST_BIT); 
	glListBase(base - 32);     
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib(); 
}

GLFont::~GLFont()
{
	Release();
}