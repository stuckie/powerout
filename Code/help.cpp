#include "externs.h"

void show_help ( void )
{
	drawRectangle (backHDC, 90, 75, 930, 615, 10, 0, 0, 0, 255, 0, 0);
	SetBkMode(backHDC, TRANSPARENT);
	SetTextColor(backHDC, RGB(255, 255, 255));
	TextOutA( backHDC, 450, 100, str_paused, (int)strlen(str_paused));
	TextOutA( backHDC, 420, 120, str_pressSpace, (int)strlen(str_pressSpace));
	TextOutA( backHDC, 120, 200, str_help1, (int)strlen(str_help1));
	TextOutA( backHDC, 120, 220, str_help2, (int)strlen(str_help2));
	TextOutA( backHDC, 120, 240, str_help3, (int)strlen(str_help3));
	TextOutA( backHDC, 120, 260, str_help4, (int)strlen(str_help4));
	TextOutA( backHDC, 120, 280, str_help5, (int)strlen(str_help5));
	TextOutA( backHDC, 120, 300, str_help6, (int)strlen(str_help6));
	TextOutA( backHDC, 120, 320, str_help7, (int)strlen(str_help7));
	TextOutA( backHDC, 120, 340, str_help8, (int)strlen(str_help8));
	TextOutA( backHDC, 120, 360, str_help9, (int)strlen(str_help9));
	TextOutA( backHDC, 120, 380, str_help10, (int)strlen(str_help10));
	TextOutA( backHDC, 120, 400, str_help11, (int)strlen(str_help11));
	TextOutA( backHDC, 120, 420, str_help12, (int)strlen(str_help12));
	TextOutA( backHDC, 120, 440, str_help13, (int)strlen(str_help13));
	TextOutA( backHDC, 450, 480, str_help14, (int)strlen(str_help14));
	//displayFrame();
}
