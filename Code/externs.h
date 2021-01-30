#pragma once

#include <windows.h>
#include "mp3_play.h"

extern bool		keys[256];			//Array to hold all our key presses
extern bool		paused;			//Wither the game is paused or not.. obviously ;)
extern int		game_status;		//Which status the game is in:
// status 0 : init | 1 : intro | 2 : game | 3 : level win | 4 : level fail | 5 : credits
extern int		tries;
extern int score;
extern int lastscore;
extern short selected;	// 1 = mirrors | 2 = wires
extern int energy;		// How much energy we got for this level
extern int needed;		// How much the factories need
extern int timeleft;		// How much time we've got to do it in
extern int laser;		// If the laser is on or not :)
extern float t;
extern int music_playing;


extern HBITMAP	FrontBuffer;
extern HBITMAP	BackBuffer;	//Two Bitmaps for our Front and Back Buffers
extern HWND		ghwnd;				//The window which receives all of Windows Messages
extern RECT		screenRect;			//The Screen itself (well, screens are rectangular)
extern HDC	backHDC;
extern HDC	 frontHDC;		//Hardware device contexts for the Buffers
extern CMP3_MCI	MyMP3;				//Creates a holder for our background music

typedef struct Mouse
{
	int x, y;				// X,Y Co-ords of Mouse Pointer
	bool left, right;			// If the Left or Right Mouse Button's been pressed.
} Mouse;

extern Mouse MousePos;

// BITMAPS
extern HBITMAP backgroundBMP;
extern HBITMAP ballBMP;
extern HBITMAP ball2BMP;
extern HBITMAP blankBMP;
extern HBITMAP factoryBMP;
extern HBITMAP factoryPowerBMP;
extern HBITMAP mirror1BMP;
extern HBITMAP mirror2BMP;
extern HBITMAP wire1BMP;
extern HBITMAP wire2BMP;
extern HBITMAP wire3BMP;
extern HBITMAP wire4BMP;
extern HBITMAP wire5BMP;
extern HBITMAP wire6BMP;
extern HBITMAP laserPowerBMP;
extern HBITMAP laserChangeBMP;
extern HBITMAP wallBMP;
extern HBITMAP BUT_mirrorsBMP;
extern HBITMAP BUT_powerBMP;
extern HBITMAP BUT_wiresBMP;
extern HBITMAP BUT_quitBMP;
extern HBITMAP BUT_retryBMP;

// HDCs
extern HDC backgroundHDC;
extern HDC ballHDC;
extern HDC ball2HDC;
extern HDC blankHDC;
extern HDC factoryHDC;
extern HDC factoryPowerHDC;
extern HDC mirror1HDC;
extern HDC mirror2HDC;
extern HDC wire1HDC;
extern HDC wire2HDC;
extern HDC wire3HDC;
extern HDC wire4HDC;
extern HDC wire5HDC;
extern HDC wire6HDC;
extern HDC laserPowerHDC;
extern HDC laserChangeHDC;
extern HDC wallHDC;
extern HDC BUT_mirrorsHDC;
extern HDC BUT_powerHDC;
extern HDC BUT_wiresHDC;
extern HDC BUT_quitHDC;
extern HDC BUT_retryHDC;

// DEFINES
#define str_demo1 "This is just a demo!"
#define str_demo2 "And you've finished it!"
#define str_demo3 "Check out the site for more levels"
#define str_demo4 "And maybe a level editor too ;)"
#define str_welldone "Well Done! On to the next one!"
#define str_failed "YOU FAILED THE LEVEL!!!"
#define str_menu "Press F4 For Menu"
#define str_pressSpace "Press Space To Continue"

#define str_paused "- = PAUSED = -"
#define str_help1 "The Main Grid has failed! All we have left is the backup grid which isn't the most stable piece of equipment"
#define str_help2 "It's also incomplete, but we must get power to the factories to complete the shift!"
#define str_help3 "This thing is so old it uses a laser>energy conversion unit."
#define str_help4 "So we're going to have to direct the laser particles to it via mirrors." 
#define str_help5 "Left-clicking in the grid when you have mirrors in your hand should place one. Same with wires."
#define str_help6 "We don't know what's in the box so it's potluck what you get."
#define str_help7 "The good news is that you can take components back out by right-clicking if you need the space."
#define str_help8 "However, the constant changing of components does not fair well with The Management."
#define str_help9 "The Convertor turns your laser particles into Charge particles which the factories need."
#define str_help10 "So build a path from the Convertor to the factories."
#define str_help11 "Again, due to the age of this system, the wires tend to burnout."
#define str_help12 "The wires also have resistance so make sure you've got the shortest path and backup paths!"
#define str_help13 "We've got to get this done quick as we've only got a limited amount of energy in our backup generators!"
#define str_help14 "SO GET TO IT!!!"

#define str_powerout "PowerOUT"
#define str_gameby   "A game by Steven -=STUCKIE=- Campbell"
#define str_siteurl  "http://www.stuckiegamez.co.uk"
#define str_sgamez   "stuckieGAMEZ Presents"
#define str_help     "F1: Help / Pause"
#define str_new_game "F2: New Game"
#define str_credits  "F3: Credits"
#define str_back     "F4: Back Here"
#define str_quit_game "ESC: Quit Game"

#define str_next "Next Tile"
#define str_score "Score:"
#define str_energy "Energy:"
#define str_needed "Needed:"
#define str_tries "Tries:"
#define str_time "Time Left:"

#define pi 3.141592625
#define MAX_BALLS 7
#define str_musicby "Music: Steven Campbell"
#define str_codeby  "Code : Steven Campbell"
#define str_gfxby   "GFX  : Steven Campbell"
#define str_based1  "GFX Programming Coursework"
#define str_based2  "For November 25th 2005"

void RegisterMyWindow(HINSTANCE hInstance);
bool InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow);
void init_game(void);
void setBuffers(void);
void loadSprites(void);
void loadBackground(void);
void killGFX(void);

void drawSprite(int x, int y, HDC sprite);
//void drawTransparentSprite ( int x, int y, HDC sprite); // for Win32
void drawRectangle(HDC hdc, int x, int y, int x2, int y2, int penSize,
	int colR, int colG, int colB, int penR, int penG, int penB);
void drawCurrent(int x, int y);
void drawCharge(int x, int y);
void drawInterface(void);

void ballSetup(void);
void ballMove(int ball, int x, int y, int t);
void menuCode(void);
void game_intro(void);

void show_help (void);
void show_credits( void );

void playMusic(void);

void gameSetup ( void );
void game ( void );
void setStack ( void );
void nextStack ( void );
void pushStack(int v, int *st, int * p);
void popStack(int * pv, int *st, int * pp);
int topStack(int *st, int pp);
void levelSetup ( int level );
void drawLevel ( void );
void levelFail ( void );
void levelWin ( void );
void drawLaser ( void );
void runWires ( void );