#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_helper.h"
#include "simon_helper.h"

void playSound(char color){
	static const char *MY_COOL_MP3;
	switch(color)
	{
		case 'G':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/colors/gSound.mp3";
			break;
		case 'R':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/colors/rSound.mp3";
			break;				
		case 'B':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/colors/bSound.mp3";
			break;
		case 'Y':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/colors/ySound.mp3";
			break;	
		case 'X':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/game_over.mp3";
			break;
		case 'N':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/navigate.mp3";
			break;
		case 'P':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/push.mp3";
			break;
		case 'S':
			MY_COOL_MP3 = "sdmc:/switch/simon-nx/sounds/start_game.mp3";
			break;				
		default:
			break;
	}
  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1280);
  Mix_Music *music = Mix_LoadMUS(MY_COOL_MP3);
	Mix_PlayMusic(music, 1);

	if(color=='X')
	{
		SDL_Delay(1000);
	}
	else if(color=='S')
	{
		SDL_Delay(2000);
	}
	else if(color=='N')
	{
		SDL_Delay(100);
	}
	else if(color=='P')
	{
		SDL_Delay(600);
	}	
	else
	{
		SDL_Delay(200);
	}
    Mix_FreeMusic(music);
}
void turnONcolor(char color){
	
	switch(color){
		case 'G':
			renderTexture(colorM4_on[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
			break;
		case 'R':
			renderTexture(colorM4_on[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red
			break;
		case 'Y':
			renderTexture(colorM4_on[2].texture, renderer, 0, 0, 302, 145, 201, 436);//Yellow
			break;
		case 'B':
			renderTexture(colorM4_on[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
			break;
		default:
			break;	
	}
}
