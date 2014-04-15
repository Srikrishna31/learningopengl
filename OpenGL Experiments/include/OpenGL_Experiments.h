#ifndef _OPENGL_EXP
#define _OPENGL_EXP

#include "stdafx.h"

class OpenGLExp
{
    HDC			hDC;    		// Private GDI Device Context
    HGLRC		hRC;	    	// Permanent Rendering Context
    bool	    fullscreen; 	// Fullscreen Flag Set To Windowed Mode By Default

public:

    OpenGLExp();
    ~OpenGLExp();

    GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// Resize And Initialize The GL Window
    int InitGL(GLvoid); 										// All Setup For OpenGL Goes Here
    int DrawGLScene(GLvoid);									// Here's Where We Do All The Drawing
    GLvoid ReleaseContext(GLvoid);								// Properly Kill The Window
    BOOL OpenGLExp::CreateGLContext(HDC hDC, int bits, int width, int height);
};

#endif
