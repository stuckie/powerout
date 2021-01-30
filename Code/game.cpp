#include "externs.h"
#include <cstdio>

#if defined(WINEGCC)
	#define FOPEN(a, b, c) a = fopen(b, c)
#else
	#define FOPEN(a, b, c) fopen_s(&a, b, c)
#endif

// GLOBALS
char game_board[9][14]; // Creates a 14x9 gameboard [y][x]
int level_setup = 0;	// if our level has been created yet
int current_level = 0;	// what level we are on...
int mirror[1];		// next mirror
int wire[1];		// next wire
int lasttile[1];	// last tile charge was on
int lasttileSTP = 0;
int mirrorSTP = 0;	// Mirror STack Pointer
int wireSTP = 0;	// Wire STack Pointer
int placed=0;		// if a tile's been placed
int gridplace;		// what gets shoved in the grid
int laserx, lasery;	// where laser is
int laserdir=0;		// the direction the laser is going ( 0 UP | 1 RIGHT | 2 DOWN | 3 LEFT )
int laserstartx,
    laserstarty;	// where the laser factory is
int laserSetup=0;
int chargedir=0;
int chargeSetup=0;
int chargex,chargey,chargestartx,chargestarty;
int timedelay=0;
int energydown=15;
int wiresburn=6000;

void gameSetup ( void )
{
	current_level=0;
	level_setup = 0;
	score = 0;
	tries = 3;
	setStack();
}

void game ( void )
{
	if (current_level<10)
		{
			int top=0;
			int gridx = ((MousePos.x - 30) / 60)-1;
			int gridy = ((MousePos.y - 15) / 60)-1;
			levelSetup ( current_level );
			drawLevel();
			drawInterface();
			nextStack();
			
			if (keys[VK_F9]==TRUE)
			{
				music_playing=0;
				game_status=3;
			}
			
			if (keys[VK_F8]==TRUE)
			{
				music_playing=0;
				game_status=4;
			}
			
			timedelay++;
			if (timedelay==75)
				{
				timeleft--;
				timedelay=0;
				}
			if((MousePos.x>90 && MousePos.x<930) && (MousePos.y>75 && MousePos.y<615))
			{
				if (MousePos.left==FALSE && placed==1) placed=0;
				if (MousePos.right==FALSE && placed==1) placed=0;
				if ((selected==1) && (MousePos.left==TRUE) && placed==0 && game_board[gridy][gridx]=='0')
				{
					popStack(&gridplace, mirror, &mirrorSTP);
					if (gridplace==1) game_board[gridy][gridx]='7';
					if (gridplace==0) game_board[gridy][gridx]='8';
					pushStack(rand()%2, mirror, &mirrorSTP);
					placed=1;
				}
				if ((selected==2) && (MousePos.left==TRUE) && placed==0 && game_board[gridy][gridx]=='0')
				{
					popStack(&gridplace, wire, &wireSTP);
					if (gridplace==1) game_board[gridy][gridx]='1';
					if (gridplace==2) game_board[gridy][gridx]='1';
					if (gridplace==3) game_board[gridy][gridx]='2';
					if (gridplace==4) game_board[gridy][gridx]='2';
					if (gridplace==5) game_board[gridy][gridx]='3';
					if (gridplace==6) game_board[gridy][gridx]='4';
					if (gridplace==7) game_board[gridy][gridx]='5';
					if (gridplace==0) game_board[gridy][gridx]='6';
					pushStack(rand()%8, wire, &wireSTP);
					placed=1;
				}
				if (MousePos.right==TRUE)
				{
					if (	game_board[gridy][gridx]=='1' ||
						game_board[gridy][gridx]=='2' ||
						game_board[gridy][gridx]=='3' ||
						game_board[gridy][gridx]=='4' ||
						game_board[gridy][gridx]=='5' ||
						game_board[gridy][gridx]=='6' ||
						game_board[gridy][gridx]=='7' ||
						game_board[gridy][gridx]=='8')
					{ game_board[gridy][gridx]='0'; score-=100; }
				}
			}
			
			if (laser==0)
				laserSetup=0;
			if (laser==1 && energy>0)
			{
				wiresburn--;
				if (wiresburn==0)
				{
					wiresburn=6000;
					int wirex, wirey;
					wirey=rand()%9;
					wirex=rand()%14;
					if (	game_board[wirey][wirex]=='1' ||
						game_board[wirey][wirex]=='2' ||
						game_board[wirey][wirex]=='3' ||
						game_board[wirey][wirex]=='4' ||
						game_board[wirey][wirex]=='5' ||
						game_board[wirey][wirex]=='6')
						game_board[wirey][wirex]='0';
				}
				 drawLaser();
			}
			if (energy>0)
				runWires();
			if (needed==0){
				music_playing=0;
				game_status=3;
				}
			if (timeleft==0){
				music_playing=0;
				game_status=4;
				}
			if (energydown==0)
			{
				energy--;
				energydown=45;
			}
		}
	if (current_level==10)
		{
		drawRectangle (backHDC, 350, 290, 700, 460, 10, 0, 0, 0, 255, 0, 0);
		SetBkMode(backHDC, TRANSPARENT);
		SetTextColor(backHDC, RGB(t-(t-1), t*t, t+t));
		TextOutA(backHDC, 430, 300, str_demo1, (int)strlen(str_demo1));
		TextOutA(backHDC, 425, 340, str_demo2, (int)strlen(str_demo2));
		TextOutA(backHDC, 400, 380, str_demo3, (int)strlen(str_demo3));
		TextOutA(backHDC, 405, 400, str_demo4, (int)strlen(str_demo4));
		TextOutA(backHDC, 430, 420, str_menu, (int)strlen(str_menu));
		t++;
		if (keys[VK_F4]==TRUE)
			music_playing=0;
			game_status=1;
		}
}

void levelWin( void )
{
	drawRectangle (backHDC, 90, 90, 930, 150, 10, 0, 0, 0, 255, 0, 0);
	SetBkMode(backHDC, TRANSPARENT);
	SetTextColor(backHDC, RGB(255, 255, 255));
	TextOutA( backHDC, 420, 100, str_welldone, strlen(str_welldone));
	TextOutA( backHDC, 420, 120, str_pressSpace, strlen(str_pressSpace));
	if (keys[VK_SPACE]==TRUE)
	{
		current_level++;
		score+=500;
		level_setup=0;
		music_playing=0;
		game_status=2;
	}
}

void levelFail( void )
{
	drawRectangle (backHDC, 90, 90, 930, 150, 10, 0, 0, 0, 255, 0, 0);
	SetBkMode(backHDC, TRANSPARENT);
	SetTextColor(backHDC, RGB(255, 255, 255));
	TextOutA( backHDC, 420, 100, str_failed, strlen(str_failed));
	TextOutA( backHDC, 420, 120, str_pressSpace, strlen(str_pressSpace));
	if (keys[VK_SPACE]==TRUE && tries>1)
	{
		tries--;
		music_playing=0;
		level_setup=0;
		game_status=2;
	}
	else if (keys[VK_SPACE]==TRUE && tries==1)
	{
		current_level=0;
		music_playing=0;
		game_status=0;
	}
}

void drawLaser ( void )
{
	if (laserSetup==0)
	{
		laserx=laserstartx+27; 
		lasery=laserstarty+12;
		laserdir=0;
		laserSetup=1;
	}
	if (chargeSetup==0)
	{
		int changedir = 0;
		COLORREF laserPos = GetPixel(backHDC, laserx, lasery);
		//if (RGB(1,1,1)==laserPos) laserdir++;
		if ((RGB(1,1,1)==laserPos) && laserdir==0 && changedir==0)
			{ laserdir=3; changedir=1; }
		if ((RGB(1,1,1)==laserPos) && laserdir==3 && changedir==0)
			{ laserdir=0; changedir=1; }
		if ((RGB(1,1,1)==laserPos) && laserdir==1 && changedir==0)
			{ laserdir=2; changedir=1; }
		if ((RGB(1,1,1)==laserPos) && laserdir==2 && changedir==0)
			{ laserdir=1; changedir=1; }
		if ((RGB(1,3,1)==laserPos) && laserdir==0 && changedir==0)
			{ laserdir=1; changedir=1; }
		if ((RGB(1,3,1)==laserPos) && laserdir==1 && changedir==0)
			{ laserdir=0; changedir=1; }
		if ((RGB(1,3,1)==laserPos) && laserdir==2 && changedir==0)
			{ laserdir=3; changedir=1; }
		if ((RGB(1,3,1)==laserPos) && laserdir==3 && changedir==0)
			{ laserdir=2; changedir=1; }
		if (RGB(255,255,255)==laserPos) changedir=0;
		if (RGB(2,2,2)==laserPos) { chargeSetup=2; laserSetup=0; }
		if (laserx<90 || laserx>930 || lasery>615 || lasery<75 || (RGB(1,2,1)==laserPos)) { energy-=10; laserSetup=0; }
		if (laserdir==4) laserdir=0;
		if (laserdir==0) { lasery-=5; score+=2; }
		if (laserdir==1) { laserx+=5; score+=2; }
		if (laserdir==2) { lasery+=5; score+=2; }
		if (laserdir==3) { laserx-=5; score+=2; }
		drawCurrent(laserx,lasery);
	}
}

void runWires ( void )
{
	int lastile;
	int gridx;
	if (chargedir==1) gridx = ((chargex-30) / 60)-1;
	if (chargedir==0) gridx = ((chargex) / 60)-1;
	if (chargedir==2) gridx = ((chargex) / 60)-1;
	if (chargedir==3) gridx = ((chargex+15)/60)-1;
	int gridy;
	if (chargedir==0) gridy = ((chargey+40) / 60)-1;
	else gridy = ((chargey) /60)-1;
	
	if (chargeSetup==0)
	{
		chargex=chargestartx;
		chargey=chargestarty;
	}
	
	if (chargeSetup==2)
	{
		chargex=chargestartx;
		chargey=chargestarty-15;
		chargedir=laserdir;
		score+=50;
		chargeSetup=1;
		popStack(&lastile, lasttile, &lasttileSTP);
		pushStack(0, lasttile, &lasttileSTP);
	}
	
	if (chargeSetup==1)
	{
		
		if (chargedir==4) chargedir=0;
		if (chargedir==0) { chargey-=2; score+=5; energydown--; }
		if (chargedir==1) { chargex+=2; score+=5; energydown--; }
		if (chargedir==2) { chargey+=2; score+=5; energydown--; }
		if (chargedir==3) { chargex-=2; score+=5; energydown--; }
		
		popStack(&lastile, lasttile, &lasttileSTP);

		if ((game_board[gridy][gridx]=='1') && (chargedir==1 || chargedir==3))
			{ energy-=10; chargeSetup=0;  }
		if ((game_board[gridy][gridx]=='2') && (chargedir==0 || chargedir==2))
			{ energy-=10; chargeSetup=0; }
			
		if ((game_board[gridy][gridx]=='1'))
			{ lastile=game_board[gridy][gridx];   }
		if ((game_board[gridy][gridx]=='2'))
			{ lastile=game_board[gridy][gridx];  }
			
		if ((game_board[gridy][gridx]=='0') ||
		    (game_board[gridy][gridx]=='w') ||
		    (game_board[gridy][gridx]=='7') ||
		    (game_board[gridy][gridx]=='8')) { energy-=10; chargeSetup=0; }
  
		if ((game_board[gridy][gridx]=='3') && chargedir==0) { chargedir=1; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='3') && chargedir==3) { chargedir=2; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='3') && (chargedir==1 || chargedir==2)
		&& (lastile==49 || lastile==50 || lastile==52 || lastile==54))
		{ energy-=10; chargeSetup=0; }
			
		if ((game_board[gridy][gridx]=='4') && chargedir==1) { chargedir=2; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='4') && chargedir==0) { chargedir=3; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='4') && (chargedir==2 || chargedir==3)
		&& (lastile==49 || lastile==50 || lastile==51 || lastile==53))
		{ energy-=10; chargeSetup=0; }
			
		if ((game_board[gridy][gridx]=='5') && chargedir==1) { chargedir=0; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='5') && chargedir==2) { chargedir=3; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='5') && (chargedir==0 || chargedir==3)
		&& (lastile==49 || lastile==50 || lastile==52 || lastile==54))
		{ energy-=10; chargeSetup=0; }
			
		if ((game_board[gridy][gridx]=='6') && chargedir==2) { chargedir=1; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='6') && chargedir==3) { chargedir=0; lastile=game_board[gridy][gridx]; }
		if ((game_board[gridy][gridx]=='6') && (chargedir==0 || chargedir==1)
		&& (lastile==49 || lastile==50 || lastile==51 || lastile==53))
		{ energy-=10; chargeSetup=0; }
			
		if (chargex<90 || chargex>930 || chargey>615 || chargey<55) { energy-=10; chargeSetup=0; }
		if ((game_board[gridy][gridx]=='f') && energy>24) { energy-=25; needed-=25; score+=100; chargeSetup=0; }
		else if ((game_board[gridy][gridx]=='f') && energy<25) { chargeSetup=0; }
		
		pushStack(lastile, lasttile, &lasttileSTP);
		
		drawCharge(chargex+30, chargey+30);
	}
}

void nextStack ( void )
{
	if (selected==1)
	{
		for (int a=3; a>0; a--)
			{
				if (topStack(mirror, mirrorSTP-1)==1)
					drawSprite( 90, 660, mirror1HDC);
				if (topStack(mirror, mirrorSTP-1)==0)
					drawSprite( 90, 660, mirror2HDC);
			}
	}
	if (selected==2)
	{
		for (int a=3; a>0; a--)
			{
				if (topStack(wire, wireSTP-1)==1)
					drawSprite( 90, 660, wire1HDC);
				if (topStack(wire, wireSTP-1)==2)
					drawSprite( 90, 660, wire1HDC);
				if (topStack(wire, wireSTP-1)==3)
					drawSprite( 90, 660, wire2HDC);
				if (topStack(wire, wireSTP-1)==4)
					drawSprite( 90, 660, wire2HDC);
				if (topStack(wire, wireSTP-1)==5)
					drawSprite( 90, 660, wire3HDC);
				if (topStack(wire, wireSTP-1)==6)
					drawSprite( 90, 660, wire4HDC);
				if (topStack(wire, wireSTP-1)==7)
					drawSprite( 90, 660, wire5HDC);
				if (topStack(wire, wireSTP-1)==0)
					drawSprite( 90, 660, wire6HDC);
			}
	}
}

void pushStack(int v, int *st, int *pp)
{
	st[(*pp)++] = v;
}

void popStack(int * pv, int *st, int *pp)
{
	*pv = st[--(*pp)];
}

int topStack(int *st, int p)
{
	return st[p];
}

int stack_empty(int &p)
{
        return p = 0;
}


void setStack ( void )
{
	stack_empty(wireSTP);
	stack_empty(mirrorSTP);
	stack_empty(lasttileSTP);
	pushStack(rand()%8, wire, &wireSTP);
	pushStack(rand()%2, mirror, &mirrorSTP);
	pushStack(0, lasttile, &lasttileSTP);
}

void levelSetup ( int level )
{
	if (level_setup==0)
	{
		FILE *levelFile = NULL;
		
		if (level==0){
			FOPEN(levelFile, "Levels/level0","r");
			needed=200;
			timeleft=500;
			energy=600;
			}
		if (level==1){
			FOPEN(levelFile, "Levels/level1","r");
			needed=300;
			timeleft=500;
			energy=600;
			}
		if (level==2){
			FOPEN(levelFile, "Levels/level2","r");
			needed=400;
			timeleft=1000;
			energy=900;
			}
		if (level==3){
			FOPEN(levelFile, "Levels/level3","r");
			needed=400;
			timeleft=800;
			energy=600;
			}
		if (level==4){
			FOPEN(levelFile, "Levels/level4","r");
			needed=300;
			timeleft=700;
			energy=600;
			}
		if (level==5){
			FOPEN(levelFile, "Levels/level5","r");
			needed=300;
			timeleft=800;
			energy=600;
			}
		if (level==6){
			FOPEN(levelFile, "Levels/level6","r");
			needed=300;
			timeleft=300;
			energy=400;
			}
		if (level==7){
			FOPEN(levelFile, "Levels/level7","r");
			needed=200;
			timeleft=600;
			energy=700;
			}
		if (level==8){
			FOPEN(levelFile, "Levels/level8","r");
			needed=600;
			timeleft=800;
			energy=900;
			}
		if (level==9){
			FOPEN(levelFile, "Levels/level9","r");
			needed=300;
			timeleft=800;
			energy=700;
			}
			
		if (levelFile==NULL) perror ("Error opening file");
		else
		{
			for ( int y=0; y<9; y++)
				for( int x=0; x<14; x++)
					game_board[y][x]=getc(levelFile);
		
		fclose (levelFile);
		}
	laser=0;
	level_setup=1;
	}
}

void drawLevel ( void )
{
	for ( int y=0; y<9; y++)
		for( int x=0; x<14; x++)
			{
				int xpos = 90 + (x*60);
				int ypos = 75 + (y*60);
				if (game_board[y][x]=='0')
					drawSprite( xpos, ypos, blankHDC);
				if (game_board[y][x]=='w')
					drawSprite( xpos, ypos, wallHDC);
				if (game_board[y][x]=='f')
					drawSprite( xpos, ypos, factoryPowerHDC);
				if (game_board[y][x]=='F')
					drawSprite( xpos, ypos, factoryHDC);
				if (game_board[y][x]=='l')
					{
					drawSprite( xpos, ypos, laserPowerHDC);
					laserstartx=xpos; laserstarty=ypos;
					}
				if (game_board[y][x]=='c')
					{
					drawSprite( xpos, ypos, laserChangeHDC);
					chargestartx=xpos; chargestarty=ypos;
					}
				if (game_board[y][x]=='1')
					drawSprite( xpos, ypos, wire1HDC);
				if (game_board[y][x]=='2')
					drawSprite( xpos, ypos, wire2HDC);
				if (game_board[y][x]=='3')
					drawSprite( xpos, ypos, wire3HDC);
				if (game_board[y][x]=='4')
					drawSprite( xpos, ypos, wire4HDC);
				if (game_board[y][x]=='5')
					drawSprite( xpos, ypos, wire5HDC);
				if (game_board[y][x]=='6')
					drawSprite( xpos, ypos, wire6HDC);
				if (game_board[y][x]=='7')
					drawSprite( xpos, ypos, mirror1HDC);
				if (game_board[y][x]=='8')
					drawSprite( xpos, ypos, mirror2HDC);
			}
}
