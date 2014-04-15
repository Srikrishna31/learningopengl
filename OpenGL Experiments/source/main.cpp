#include "OpenGL_Experiments.h"
#include "resource.h"

bool	    keys[256];		// Array Used For The Keyboard Routine
bool	    active=TRUE;	// Window Active Flag Set To TRUE By Default
HWND		hWnd;		    // Holds Our Window Handle
HINSTANCE	hMyInstance;		// Holds The Instance Of The Application

static LRESULT CALLBACK WndProc(HWND hWnd, UINT	uMsg,  WPARAM wParam, LPARAM lParam, OpenGLExp* pGL);
void KillWindow(bool fullscreen);

BOOL createWindow(int width, int height, bool fullscreenflag, const char* title, int bits)
{
    WNDCLASS	wc;						// Windows Class Structure
    DWORD		dwExStyle;				// Window Extended Style
    DWORD		dwStyle;				// Window Style
    RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
    WindowRect.left=(long)0;			// Set Left Value To 0
    WindowRect.right=(long)width;		// Set Right Value To Requested Width
    WindowRect.top=(long)0;				// Set Top Value To 0
    WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

    hMyInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
    wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
    wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
    wc.cbClsExtra		= 0;									// No Extra Window Data
    wc.cbWndExtra		= 0;									// No Extra Window Data
    wc.hInstance		= hMyInstance;							// Set The Instance
    wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
    wc.hbrBackground	= NULL;									// No Background Required For GL
    wc.lpszMenuName		= NULL;									// We Don't Want A Menu
    wc.lpszClassName	= LPCSTR("OpenGL");								// Set The Class Name

    if (!RegisterClassA(&wc))									// Attempt To Register The Window Class
    {
        MessageBox(NULL,LPCSTR("Failed To Register The Window Class."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;											// Return FALSE
    }

    if (fullscreenflag)											// Attempt Fullscreen Mode?
    {
        DEVMODE dmScreenSettings;								// Device Mode
        memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
        dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
        dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
        dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
        dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
        dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
        if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
        {
            // If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
            if (MessageBox(NULL,LPCSTR("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?")
                ,LPCSTR("NeHe GL"),MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
            {
                fullscreenflag=FALSE;	// Windowed Mode Selected.  Fullscreen = FALSE
            }
            else
            {
                // Pop Up A Message Box Letting User Know The Program Is Closing.
                MessageBox(NULL,LPCSTR("Program Will Now Close."),LPCSTR("ERROR"),MB_OK|MB_ICONSTOP);
                return FALSE;									// Return FALSE
            }
        }
    }

    if (fullscreenflag)												// Are We Still In Fullscreen Mode?
    {
        dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
        dwStyle=WS_POPUP;										// Windows Style
        ShowCursor(FALSE);										// Hide Mouse Pointer
    }
    else
    {
        dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
        dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
    }

    AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

    // Create The Window
    if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
                                LPCSTR("OpenGL"),							// Class Name
                                LPCSTR(title),								// Window Title
                                dwStyle |							// Defined Window Style
                                WS_CLIPSIBLINGS |					// Required Window Style
                                WS_CLIPCHILDREN,					// Required Window Style
                                0, 0,								// Window Position
                                WindowRect.right-WindowRect.left,	// Calculate Window Width
                                WindowRect.bottom-WindowRect.top,	// Calculate Window Height
                                NULL,								// No Parent Window
                                NULL,								// No Menu
                                hMyInstance,							// Instance
                                NULL)))								// Dont Pass Anything To WM_CREATE
    {
        KillWindow(fullscreenflag);								// Reset The Display
        MessageBox(NULL,LPCSTR("Window Creation Error."),LPCSTR("ERROR"),MB_OK|MB_ICONEXCLAMATION);
        return FALSE;								// Return FALSE
    }

    return TRUE;
}

void showWindow()
{
    ShowWindow(hWnd,SW_SHOW);						// Show The Window
    SetForegroundWindow(hWnd);						// Slightly Higher Priority
    SetFocus(hWnd);									// Sets Keyboard Focus To The Window
}

void KillWindow(bool fullscreen)
{
    HDC hDC = GetDC(hWnd);

    if (fullscreen)										// Are We In Fullscreen Mode?
    {
        ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
        ShowCursor(TRUE);								// Show Mouse Pointer
    }

        if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
    {
        MessageBox(NULL,LPCSTR(("Release Device Context Failed.")),LPCSTR("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
        hDC=NULL;										// Set DC To NULL
    }

    if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
    {
        MessageBox(NULL,LPCSTR("Could Not Release hWnd."),LPCSTR("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
        hWnd=NULL;										// Set hWnd To NULL
    }

    if (!UnregisterClass(LPCSTR("OpenGL"),hMyInstance))			// Are We Able To Unregister Class
    {
        MessageBox(NULL,LPCSTR("Could Not Unregister Class."),LPCSTR("SHUTDOWN ERROR"),MB_OK | MB_ICONINFORMATION);
        hMyInstance=NULL;									// Set hInstance To NULL
    }
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
                    HINSTANCE	hPrevInstance,		// Previous Instance
                    LPSTR		lpCmdLine,			// Command Line Parameters
                    int			nCmdShow)			// Window Show State
{
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    MSG		msg;									// Windows Message Structure
    BOOL	done=FALSE;								// Bool Variable To Exit Loop
    bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

    OpenGLExp ogl;
    hMyInstance = hInstance;
    // Ask The User Which Screen Mode They Prefer
    if (MessageBox(NULL,LPCSTR("Would You Like To Run In Fullscreen Mode?"), LPCSTR("Start FullScreen?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
    {
        fullscreen=FALSE;							// Windowed Mode
    }

    // Create Our OpenGL Window
    BOOL bWinCreate = createWindow(640, 480, fullscreen, "NeHe's OpenGL Framework", 16);
    BOOL bContextCreate = ogl.CreateGLContext(GetDC(hWnd), 16, 640, 480);
    if (!bWinCreate && !bContextCreate)
    {
        return 0;									// Quit If Window Was Not Created
    }

    showWindow();
    while(!done)
    {
        if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
        {
            if (msg.message==WM_QUIT)
            {
                done=TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
            if (active)
            {
                if (keys[VK_ESCAPE])
                {
                    done=TRUE;
                }
                else
                {
                    ogl.DrawGLScene();
                }
            }

            if (keys[VK_F1])
            {
                keys[VK_F1]=FALSE;
                ogl.ReleaseContext();
                KillWindow(fullscreen);
                fullscreen=!fullscreen;
                // Recreate Our OpenGL Window
                bWinCreate = createWindow(640, 480, fullscreen, "NeHe's OpenGL Framework", 16);
                bContextCreate = ogl.CreateGLContext(GetDC(hWnd), 16, 640, 480);
                if (!bWinCreate && !bContextCreate)
                {
                    return 0;
                }
                showWindow();
            }
        }
    }

    // Shutdown
    ogl.ReleaseContext();
    KillWindow(fullscreen);
    return (msg.wParam);
}

static LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
                            UINT	uMsg,			// Message For This Window
                            WPARAM	wParam,			// Additional Message Information
                            LPARAM	lParam, OpenGLExp* pGL)			// Additional Message Information
{
    switch (uMsg)									// Check For Windows Messages
    {
        case WM_ACTIVATE:							// Watch For Window Activate Message
        {
            if (!HIWORD(wParam))					// Check Minimization State
            {
                active=TRUE;						// Program Is Active
            }
            else
            {
                active=FALSE;						// Program Is No Longer Active
            }

            return 0;								// Return To The Message Loop
        }

        case WM_SYSCOMMAND:							// Intercept System Commands
        {
            switch (wParam)							// Check System Calls
            {
                case SC_SCREENSAVE:					// Screensaver Trying To Start?
                case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
                return 0;							// Prevent From Happening
            }
            break;									// Exit
        }

        case WM_CLOSE:								// Did We Receive A Close Message?
        {
            PostQuitMessage(0);						// Send A Quit Message
            return 0;								// Jump Back
        }

        case WM_KEYDOWN:							// Is A Key Being Held Down?
        {
            keys[wParam] = TRUE;					// If So, Mark It As TRUE
            return 0;								// Jump Back
        }

        case WM_KEYUP:								// Has A Key Been Released?
        {
            keys[wParam] = FALSE;					// If So, Mark It As FALSE
            return 0;								// Jump Back
        }

        case WM_SIZE:								// Resize The OpenGL Window
        {
            pGL->ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
            return 0;								// Jump Back
        }
    }

    // Pass All Unhandled Messages To DefWindowProc
    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
