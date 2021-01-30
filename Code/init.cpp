#include "externs.h"
#include <ctime>

// POINTER setup
HBITMAP		FrontBuffer, BackBuffer;	//Two Bitmaps for our Front and Back Buffers
HWND		ghwnd;				//The window which receives all of Windows Messages
RECT		screenRect;			//The Screen itself (well, screens are rectangular)
HDC		backHDC, frontHDC;		//Hardware device contexts for the Buffers
CMP3_MCI	MyMP3;				//Creates a holder for our background music

// GLOBAL VARIABLES -- try keep these to a minimum.. this time ;)
bool		keys[256];			//Array to hold all our key presses
bool		paused = FALSE;			//Wither the game is paused or not.. obviously ;)
int		game_status = 0;		//Which status the game is in:
// status 0 : init | 1 : intro | 2 : game | 3 : level win | 4 : level fail | 5 : credits
int		tries, score, lastscore;	//Some player variables :)
short selected = 1;	// 1 = mirrors | 2 = wires
int energy;		// How much energy we got for this level
int needed;		// How much the factories need
int timeleft;		// How much time we've got to do it in
int laser=0;		// If the laser is on or not :)

// INSTANCE setup
Mouse MousePos; // create an instance of our mouse.

// BITMAPS
HBITMAP backgroundBMP;
HBITMAP ballBMP;
HBITMAP ball2BMP;
HBITMAP blankBMP;
HBITMAP factoryBMP;
HBITMAP factoryPowerBMP;
HBITMAP mirror1BMP;
HBITMAP mirror2BMP;
HBITMAP wire1BMP;
HBITMAP wire2BMP;
HBITMAP wire3BMP;
HBITMAP wire4BMP;
HBITMAP wire5BMP;
HBITMAP wire6BMP;
HBITMAP laserPowerBMP;
HBITMAP laserChangeBMP;
HBITMAP wallBMP;
HBITMAP BUT_mirrorsBMP;
HBITMAP BUT_powerBMP;
HBITMAP BUT_wiresBMP;
HBITMAP BUT_quitBMP;
HBITMAP BUT_retryBMP;

// HDCs
HDC backgroundHDC;
HDC ballHDC;
HDC ball2HDC;
HDC blankHDC;
HDC factoryHDC;
HDC factoryPowerHDC;
HDC mirror1HDC;
HDC mirror2HDC;
HDC wire1HDC;
HDC wire2HDC;
HDC wire3HDC;
HDC wire4HDC;
HDC wire5HDC;
HDC wire6HDC;
HDC laserPowerHDC;
HDC laserChangeHDC;
HDC wallHDC;
HDC BUT_mirrorsHDC;
HDC BUT_powerHDC;
HDC BUT_wiresHDC;
HDC BUT_quitHDC;
HDC BUT_retryHDC;

// PROTOTYPES for THIS FILE
void RegisterMyWindow(HINSTANCE hInstance);
bool InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow);
void init_game( void );
void setBuffers(void);
void loadSprites(void);
void loadBackground(void);
void killGFX (void);

extern LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Having Windows know we've created a window is usually a good idea ;)
// So let's go and do that.
void RegisterMyWindow(HINSTANCE hInstance)
{
	WNDCLASSEXW  wcex;					// Pointer to the window class

	wcex.cbSize        = sizeof (wcex);			// Size of the Window Class
	wcex.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Style (IE: Horizontal and Vertical redraw)
	wcex.lpfnWndProc   = WndProc;				// Which WNDPROC it belongs to (we only got one)
	wcex.cbClsExtra    = 0;					// No extra bytes for the class
	wcex.cbWndExtra    = 0;					// No extra bytes for the window either
	wcex.hInstance     = hInstance;				// The instance this belongs to
	wcex.hIcon         = 0;					// Icon in the top left of the window
	wcex.hCursor       = LoadCursor (NULL, IDC_ARROW);	// Which cursor we use
	wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);		// Default Background colour
	wcex.lpszMenuName  = NULL;				// We don't have a menu...
	wcex.lpszClassName = L"MainWindow";			// Name of this Class
	wcex.hIconSm       = 0;					// The small icon in the taskbar

	RegisterClassExW(&wcex);				// Register this class to Windows
}


bool InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND        hwnd;
	hwnd = CreateWindowW(L"MainWindow",	  // Name of the Window Class we just generated
			L"stuckieGAMEZ - PowerOUT",// What the TITLE BAR says
			WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX,
			// Set style to only have a caption, border, sys_menu and a minimize box.. no resize
			CW_USEDEFAULT,		  // Default X start
			CW_USEDEFAULT,		  // Default Y start
			1024,			  // Set width 1024
			768,			  // Set height 768
			NULL,			  // It has no parents (aww shame)
			NULL,			  // It has no menu
			hInstance,		  // Which instance it belongs to
			NULL);			  // And we don't want to pass anything to WNDPROC
			 
	if (!hwnd)				  // Now, if we don't have a windows handler
	{
		return FALSE;			  // We die...
	}

	ShowWindow (hwnd, nCmdShow);		  // Show our beautiful window to the world!
	UpdateWindow (hwnd);			  // And update it!
	ghwnd = hwnd;				  // Tell Windows to receive messages on THIS window
	return TRUE;				  // Job's done, and all done well :)

}

void loadBackground ( void )
{
	backgroundBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	backgroundHDC = CreateCompatibleDC(frontHDC);
	SelectObject ( backgroundHDC, backgroundBMP);
}

void loadSprites ( void )
{
	ballBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/ball.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ballHDC = CreateCompatibleDC(backHDC);
	SelectObject ( ballHDC, ballBMP);
	
	ball2BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/ball2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ball2HDC = CreateCompatibleDC(backHDC);
	SelectObject ( ball2HDC, ball2BMP);
	
	blankBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/blank.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	blankHDC = CreateCompatibleDC(backHDC);
	SelectObject ( blankHDC, blankBMP);
	
	factoryBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/factory.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	factoryHDC = CreateCompatibleDC(backHDC);
	SelectObject ( factoryHDC, factoryBMP);
	
	factoryPowerBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/factory-needpower.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	factoryPowerHDC = CreateCompatibleDC(backHDC);
	SelectObject ( factoryPowerHDC, factoryPowerBMP);
	
	mirror1BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/mirror1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	mirror1HDC = CreateCompatibleDC(backHDC);
	SelectObject ( mirror1HDC, mirror1BMP);
	
	mirror2BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/mirror2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	mirror2HDC = CreateCompatibleDC(backHDC);
	SelectObject ( mirror2HDC, mirror2BMP);
	
	wire1BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wire1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wire1HDC = CreateCompatibleDC(backHDC);
	SelectObject ( wire1HDC, wire1BMP);
	
	wire2BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wire2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wire2HDC = CreateCompatibleDC(backHDC);
	SelectObject ( wire2HDC, wire2BMP);
	
	wire3BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wire3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wire3HDC = CreateCompatibleDC(backHDC);
	SelectObject ( wire3HDC, wire3BMP);
	
	wire4BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wire4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wire4HDC = CreateCompatibleDC(backHDC);
	SelectObject ( wire4HDC, wire4BMP);
	
	wire5BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wire5.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wire5HDC = CreateCompatibleDC(backHDC);
	SelectObject ( wire5HDC, wire5BMP);
	
	wire6BMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wire6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wire6HDC = CreateCompatibleDC(backHDC);
	SelectObject ( wire6HDC, wire6BMP);
	
	laserPowerBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/laser-plant.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	laserPowerHDC = CreateCompatibleDC(backHDC);
	SelectObject ( laserPowerHDC, laserPowerBMP);
	
	laserChangeBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/laser-power.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	laserChangeHDC = CreateCompatibleDC(backHDC);
	SelectObject ( laserChangeHDC, laserChangeBMP);
	
	BUT_wiresBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wires.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BUT_wiresHDC = CreateCompatibleDC(backHDC);
	SelectObject ( BUT_wiresHDC, BUT_wiresBMP);
	
	BUT_mirrorsBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/mirrors.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BUT_mirrorsHDC = CreateCompatibleDC(backHDC);
	SelectObject ( BUT_mirrorsHDC, BUT_mirrorsBMP);
	
	BUT_powerBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/power.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BUT_powerHDC = CreateCompatibleDC(backHDC);
	SelectObject ( BUT_powerHDC, BUT_powerBMP);
	
	BUT_quitBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/quit.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BUT_quitHDC = CreateCompatibleDC(backHDC);
	SelectObject ( BUT_quitHDC, BUT_quitBMP);
	
	BUT_retryBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/retry.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BUT_retryHDC = CreateCompatibleDC(backHDC);
	SelectObject ( BUT_retryHDC, BUT_retryBMP);
	
	wallBMP = (HBITMAP) LoadImageW(NULL, L"Gfx/wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wallHDC = CreateCompatibleDC(backHDC);
	SelectObject ( wallHDC, wallBMP);
}

void killGFX ( void )
{
	SelectObject(backgroundHDC,backgroundBMP);
	DeleteDC(backgroundHDC);
	SelectObject(ballHDC, ballBMP);
	DeleteDC(ballHDC);
	SelectObject(ball2HDC, ball2BMP);
	DeleteDC(ball2HDC);
	SelectObject(blankHDC, blankBMP);
	DeleteDC(blankHDC);
	SelectObject(factoryHDC, factoryBMP);
	DeleteDC(factoryHDC);
	SelectObject(factoryPowerHDC, factoryPowerBMP);
	DeleteDC(factoryPowerHDC);
	SelectObject(mirror1HDC, mirror1BMP);
	DeleteDC(mirror1HDC);
	SelectObject(mirror2HDC, mirror2BMP);
	DeleteDC(mirror2HDC);
	SelectObject(wire1HDC, wire1BMP);
	DeleteDC(wire1HDC);
	SelectObject(wire2HDC, wire2BMP);
	DeleteDC(wire2HDC);
	SelectObject(wire3HDC, wire3BMP);
	DeleteDC(wire3HDC);
	SelectObject(wire4HDC, wire4BMP);
	DeleteDC(wire4HDC);
	SelectObject(wire5HDC, wire5BMP);
	DeleteDC(wire5HDC);
	SelectObject(wire6HDC, wire6BMP);
	DeleteDC(wire6HDC);
	SelectObject(laserChangeHDC, laserChangeBMP);
	DeleteDC(laserChangeHDC);
	SelectObject(laserPowerHDC, laserPowerBMP);
	DeleteDC(laserPowerHDC);
	SelectObject(wallHDC, wallBMP);
	DeleteDC(wallHDC);
	SelectObject(BUT_wiresHDC, BUT_wiresBMP);
	DeleteDC(BUT_wiresHDC);
	SelectObject(BUT_powerHDC, BUT_powerBMP);
	DeleteDC(BUT_powerHDC);
	SelectObject(BUT_mirrorsHDC, BUT_mirrorsBMP);
	DeleteDC(BUT_mirrorsHDC);
	SelectObject(BUT_quitHDC, BUT_quitBMP);
	DeleteDC(BUT_quitHDC);
	SelectObject(BUT_retryHDC, BUT_retryBMP);
	DeleteDC(BUT_retryHDC);
	
}

// Function to setup the Front and Back Buffers.
void setBuffers( void )
{
	GetClientRect(ghwnd, &screenRect);	//Grab the size of the Screen Area
	frontHDC = GetDC(ghwnd);		//Create the Front Buffer Device Context
	backHDC = CreateCompatibleDC(frontHDC); //Creates a compatible Back Buffer Device Context
	
	// Create the actual bitmaps we draw on:
	FrontBuffer = CreateCompatibleBitmap(frontHDC, screenRect.right,screenRect.bottom);
	BackBuffer = (HBITMAP)SelectObject(backHDC, FrontBuffer);
	
	BitBlt(frontHDC, screenRect.left, screenRect.top, screenRect.right, screenRect.bottom,
			backgroundHDC, 0, 0, SRCCOPY);
	
	BitBlt(backHDC, screenRect.left, screenRect.top, screenRect.right, screenRect.bottom,
			backgroundHDC, 0, 0, SRCCOPY);

}

void init_game( void )
{
	lastscore = 0;
	loadSprites();
	game_status=1;
	srand(time(NULL));
}
