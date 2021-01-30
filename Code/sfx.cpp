#include "externs.h"

int music_playing = 0;

void playMusic ( void )
{
	if(music_playing!=1)
	{
		if (game_status==1){
		MyMP3.Unload();
		MyMP3.Load("Music/Title.mp3");	// Load in the Title music
		MyMP3.Play();			// Play Music
		music_playing=1;}
	
		if (game_status==2){
		MyMP3.Unload();
		MyMP3.Load("Music/Ingame.mp3");	// Ingame Music
		MyMP3.Play();			// Play Music
		music_playing=1; }
		
		if (game_status==3){
		MyMP3.Unload();
		MyMP3.Load("Music/Level-Complete.mp3"); // Level Win music
		MyMP3.Play();			// Play Music
		music_playing=1; }
	
		if (game_status==4){
		MyMP3.Unload();
		MyMP3.Load("Music/Level-Fail.mp3");	// Level Failed
		MyMP3.Play();			// Play Music
		music_playing=1;}
	
		if (game_status==5){
		MyMP3.Unload();
		MyMP3.Load("Music/Credits.mp3");	// Credits Music
		MyMP3.Play();			// Play Music
		music_playing=1;}
	
		
	}
	if (MyMP3.IsPaused()) MyMP3.Play();
	// we don't want to keep polling or initilising our music..
}
