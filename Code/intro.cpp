#include "externs.h"
#include <math.h>

// Local(ish) Variables
int intro_balls[2][13]; // we want 5 balls onscreen, with X-Y co-ords too :)
float t=0;

void ballSetup ( void )
{
	for (int i=0; i<13; i++)
	{
		intro_balls[0][i]=640;
		intro_balls[1][i]=480;
	}
	
}

void ballMove ( int ball, int x, int y, int t )
{
	intro_balls[0][ball] = x + (int)(cos(t * 0.1f)*20);
	intro_balls[1][ball] = y + (int)(sin(t * t * 0.0033f) * sin(t * t * 0.0234f) * 100);
	drawSprite( intro_balls[0][ball], intro_balls[1][ball], ballHDC);
}

void menuCode ( void )
{
	SetTextColor(backHDC, RGB(0, 0, 0));
	TextOutA(backHDC, 430, 130, str_sgamez, (int)strlen(str_sgamez));
	TextOutA(backHDC, 480, 150, str_powerout, (int)strlen(str_powerout));
	TextOutA(backHDC, 360, 180, str_gameby, (int)strlen(str_gameby));
	TextOutA(backHDC, 440, 500, str_help, (int)strlen(str_help));
	TextOutA(backHDC, 440, 520, str_new_game, (int)strlen(str_new_game));
	TextOutA(backHDC, 440, 540, str_credits, (int)strlen(str_credits));
	TextOutA(backHDC, 440, 560, str_back, (int)strlen(str_back));
	TextOutA(backHDC, 440, 580, str_quit_game, (int)strlen(str_quit_game));
}

void game_intro ( void )
{
	drawRectangle (backHDC, 100, 210, 920, 490, 10, 0, 0, 0, 255, 0, 0);
	for (int u=0; u<13; u++)
		ballMove( u, 120+(u*60), 310, ((u+t)+u));
	menuCode();
	t+=0.1F;


}
