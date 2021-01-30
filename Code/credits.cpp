#include "externs.h"
#include <math.h>

typedef struct _BALLS
{
    int x;
    int y;
    double angle;
}BALLS;

BALLS gBalls[] = { 	0, 0, 0,
			0, 0, 25,
			0, 0, 50,
			0, 0, 75,
			0, 0, 100,
			0, 0, 125,
			0, 0, 150};

void show_credits( void )
{
	drawRectangle(backHDC, 90, 75, 930, 768, 10, 0, 0, 0, 255, 0, 0);
	int xpos = 150;
	int ypos = 400;
 	for(int i = 0; i < MAX_BALLS; i++)
	{
		double alpha = gBalls[i].angle * pi / 180;
		gBalls[i].x = xpos + 
		int((xpos - 30) * sin(alpha) * cos(alpha) * cos(2 * alpha));
		gBalls[i].y = ypos - 30 + int(265 * cos(alpha));
		drawSprite( gBalls[i].x, gBalls[i].y, ball2HDC);
		drawSprite( gBalls[i].x+630, gBalls[i].y, ballHDC);
		gBalls[i].angle+=0.1;
		SetBkMode(backHDC, TRANSPARENT);
		SetTextColor(backHDC, RGB(255, 255, 255));
		TextOutA( backHDC, gBalls[6].x+300, gBalls[6].y, str_powerout, (int)strlen(str_powerout));
		TextOutA( backHDC, gBalls[5].x+200, gBalls[5].y, str_gameby, (int)strlen(str_gameby));
		TextOutA( backHDC, gBalls[4].x+225, gBalls[4].y, str_musicby, (int)strlen(str_musicby));
		TextOutA( backHDC, gBalls[3].x+225, gBalls[3].y, str_codeby, (int)strlen(str_codeby));
		TextOutA( backHDC, gBalls[2].x+225, gBalls[2].y, str_gfxby, (int)strlen(str_gfxby));
		TextOutA( backHDC, gBalls[1].x+225, gBalls[1].y, str_based1, (int)strlen(str_based1));
		TextOutA( backHDC, gBalls[0].x+225, gBalls[0].y, str_based2, (int)strlen(str_based2));
	}
}
