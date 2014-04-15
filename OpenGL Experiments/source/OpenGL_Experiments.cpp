// OpenGL Experiments.cpp : Defines the entry point for the application.
//

#include "OpenGL_Experiments.h"

OpenGLExp::OpenGLExp()
    :hDC(NULL),hRC(NULL)
{
}

OpenGLExp::~OpenGLExp()
{
}

GLvoid OpenGLExp::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }

    glViewport(0,0,width,height);						// Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();									// Reset The Modelview Matrix
}

int OpenGLExp::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 1.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    return TRUE;										// Initialization Went OK
}

int OpenGLExp::DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix

    SwapBuffers(hDC);				// Swap Buffers (Double Buffering)

    return TRUE;										// Everything Went OK
}

GLvoid OpenGLExp::ReleaseContext(GLvoid)								// Properly Kill The Window
{
    if (hRC)											// Do We Have A Rendering Context?
    {
        if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
        {
            MessageBox(NULL,LPCSTR("Release Of DC And RC Failed."),LPCSTR(_T("SHUTDOWN ERROR")),MB_OK | MB_ICONINFORMATION);
        }

        if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
        {
            MessageBox(NULL,LPCSTR(("Release Rendering Context Failed.")),LPCSTR(_T("SHUTDOWN ERROR")),MB_OK | MB_ICONINFORMATION);
        }
        hRC=NULL;										// Set RC To NULL
    }
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
BOOL OpenGLExp::CreateGLContext(HDC hDC, int bits, int width, int height)
{
    GLuint		PixelFormat;			// Holds The Results After Searching For A Match
        static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
    {
        sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
        1,											// Version Number
        PFD_DRAW_TO_WINDOW |						// Format Must Support Window
        PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
        PFD_DOUBLEBUFFER,							// Must Support Double Buffering
        PFD_TYPE_RGBA,								// Request An RGBA Format
        bits,										// Select Our Color Depth
        0, 0, 0, 0, 0, 0,							// Color Bits Ignored
        0,											// No Alpha Buffer
        0,											// Shift Bit Ignored
        0,											// No Accumulation Buffer
        0, 0, 0, 0,									// Accumulation Bits Ignored
        16,											// 16Bit Z-Buffer (Depth Buffer)
        0,											// No Stencil Buffer
        0,											// No Auxiliary Buffer
        PFD_MAIN_PLANE,								// Main Drawing Layer
        0,											// Reserved
        0, 0, 0										// Layer Masks Ignored
    };

    if (!hDC)							// Did We Get A Device Context?
    {
        ReleaseContext();								// Reset The Display
        MessageBox(NULL,LPCSTR("Can't Create A GL Device Context."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }

    if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
    {
        ReleaseContext();								// Reset The Display
        MessageBox(NULL,LPCSTR("Can't Find A Suitable PixelFormat."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }

    if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
    {
        ReleaseContext();								// Reset The Display
        MessageBox(NULL,LPCSTR("Can't Set The PixelFormat."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }

    if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
    {
        ReleaseContext();								// Reset The Display
        MessageBox(NULL,LPCSTR("Can't Create A GL Rendering Context."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }

    if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
    {
        ReleaseContext();								// Reset The Display
        MessageBox(NULL,LPCSTR("Can't Activate The GL Rendering Context."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }
    this->hDC = hDC;
    if (!InitGL())									// Initialize Our Newly Created GL Window
    {
        ReleaseContext();								// Reset The Display
        MessageBox(NULL,LPCSTR("Initialization Failed."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }

    ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen
    return true;
}
