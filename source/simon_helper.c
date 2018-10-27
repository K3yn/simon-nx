#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_helper.h"
#include "simon_helper.h"

void playSound(char color){
	static const char *color_sound;
	if(modoAudio==4 || modoAudio==5)
	{
		switch(color)
		{
			case 'G':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/00.mp3";
				break;
			case 'R':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/03.mp3";
				break;				
			case 'B':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/06.mp3";
				break;
			case 'Y':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/09.mp3";
				break;
			case 'P':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/12.mp3";
				break;
			default:
			break;	
		}
	}
	else if(modoAudio==8)
	{
		switch(color)
		{
			case 'G':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/00.mp3";
				break;
			case 'R':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/02.mp3";
				break;				
			case 'B':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/04.mp3";
				break;
			case 'Y':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/06.mp3";
				break;
			case 'P':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/08.mp3";
				break;
			case 'O':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/10.mp3";
				break;
			case 'V':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/12.mp3";
				break;
			case 'C':
				color_sound = "sdmc:/switch/simon-nx/sounds/game/14.mp3";
				break;				
			default:
			break;	
		}
	
	}
	switch(color)
	{
		case 'X':
			color_sound = "sdmc:/switch/simon-nx/sounds/game_over.mp3";
			break;
		case 'N':
			color_sound = "sdmc:/switch/simon-nx/sounds/navigate.mp3";
			break;
		case 'A':
			color_sound = "sdmc:/switch/simon-nx/sounds/push.mp3";
			break;
		case 'S':
			color_sound = "sdmc:/switch/simon-nx/sounds/start_game.mp3";
			break;				
		default:
			break;
	}
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1280);
    Mix_Music *music = Mix_LoadMUS(color_sound);
	Mix_PlayMusic(music, 1); // Suena el sonido y luego displayea el color	
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
	else if(color=='A')
	{
		SDL_Delay(400);
	}
	else if(modoAudio==4 || modoAudio==5 || modoAudio==8)
	{
		SDL_Delay(250);
	}	

	// hacemos la pausa para que suene la musica
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
