#include "externs.h"

#if defined(WINEGCC)
	#define ITOA(a, b, c) sprintf(b,"%d",a)
#else
	#define ITOA(a, b, c) _itoa_s(a, b, c)
#endif

// GLOBALS
int buttondown=0;

void drawInterface(void)
{
	char buffer [10];
	SetBkMode(backHDC, OPAQUE);
	SetTextColor(backHDC, RGB(0,0,0));
	TextOutA(backHDC, 90, 630, str_next, (int)strlen(str_next));
	TextOutA(backHDC,400, 630, str_score,(int)strlen(str_score));
	ITOA (score,buffer,10);
	TextOutA(backHDC,500, 630, buffer,(int)strlen(buffer));
	TextOutA(backHDC,400, 650, str_energy,(int)strlen(str_energy));
	ITOA (energy,buffer,10);
	TextOutA(backHDC,500, 650, buffer,(int)strlen(buffer));
	TextOutA(backHDC,400, 670, str_needed,(int)strlen(str_needed));
	ITOA(needed,buffer,10);
	TextOutA(backHDC,500, 670, buffer,(int)strlen(buffer));
	TextOutA(backHDC,400, 690, str_tries,(int)strlen(str_tries));
	ITOA(tries,buffer,10);
	TextOutA(backHDC,500, 690, buffer,(int)strlen(buffer));
	TextOutA(backHDC,400, 710, str_time,(int)strlen(str_time));
	ITOA(timeleft,buffer,10);
	TextOutA(backHDC,500, 710, buffer,(int)strlen(buffer));
	drawSprite(860, 660, BUT_quitHDC);
	if (MousePos.left==TRUE && ((MousePos.x>860 && MousePos.x<920) && (MousePos.y>660 && MousePos.y<720)))
		game_status=0;
	drawSprite(700, 660, BUT_mirrorsHDC);
	if (MousePos.left==TRUE && ((MousePos.x>700 && MousePos.x<760) && (MousePos.y>660 && MousePos.y<720)))
		selected=1;
	drawSprite(640, 660, BUT_wiresHDC);
	if (MousePos.left==TRUE && ((MousePos.x>640 && MousePos.x<700) && (MousePos.y>660 && MousePos.y<720)))
		selected=2;
	drawSprite(540, 660, BUT_powerHDC);
	if (MousePos.left==TRUE && ((MousePos.x>540 && MousePos.x<600) && (MousePos.y>660 && MousePos.y<720)))
	if (laser==0) { laser=1; }
	
	drawSprite(240, 660, BUT_retryHDC);
	if (MousePos.left==TRUE && ((MousePos.x>240 && MousePos.x<300) && (MousePos.y>660 && MousePos.y<720)) && buttondown==0)
	{
		music_playing=0;
		game_status=4;
	}
	
	if (MousePos.left==FALSE) buttondown=0;
}


void drawRectangle (HDC hdc, int x, int y, int x2, int y2, int penSize,
		   int colR, int colG, int colB, int penR, int penG, int penB)
{
	HPEN hpen, hpenOld;
	HBRUSH hbrush, hbrushOld;

	// Create pen of colour defined by the penR/G/B ints and of penSize
	hpen = CreatePen(PS_SOLID, penSize, RGB(penR, penG, penB));
	// Create fill colour.
	hbrush = CreateSolidBrush(RGB(colR, colG, colB));

	// Select the new pen and brush, and then draw.
	hpenOld = (HPEN)SelectObject(hdc, hpen);
	hbrushOld = (HBRUSH)SelectObject(hdc, hbrush);
	Rectangle(hdc, x, y2, x2, y);

	SelectObject(hdc, hpenOld);
	DeleteObject(hpen);
	SelectObject(hdc, hbrushOld);
	DeleteObject(hbrush);
}

void drawSprite ( int x, int y, HDC sprite )
{
	BitBlt(backHDC, x, y, 60, 60, sprite, 0, 0, SRCCOPY);
}

void drawCurrent ( int x, int y )
{
	HBRUSH hbrush, hbrushOld;
	hbrush = CreateSolidBrush(RGB(255, 0, 0));
	hbrushOld = (HBRUSH)SelectObject(backHDC, hbrush);	
	Ellipse(backHDC, x, y, x+5, y+5);
	SelectObject(backHDC, hbrushOld);
	DeleteObject(hbrush);
}

void drawCharge ( int x, int y )
{
	HBRUSH hbrush, hbrushOld;
	hbrush = CreateSolidBrush(RGB(255, 255, 0));
	hbrushOld = (HBRUSH)SelectObject(backHDC, hbrush);	
	Ellipse(backHDC, x, y, x+15, y+15);
	SelectObject(backHDC, hbrushOld);
	DeleteObject(hbrush);
}

/*void drawTransparentSprite ( int x, int y, HDC sprite ) // for Win32
{
	TransparentBlt(backHDC, x, y, 60, 60, sprite, 0, 0, 60, 60, RGB(0,0,0));
}*/
