#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_helper.h"
#include "simon_helper.h"

void loadIniVars(){
	contMenuMain=4;
	contMenuModos=3;
	numAleatorio=0;
	contSemaforoSecColores=0;
	contSemaforoColorOnOff=0;
	contGameOver=0;
	t=0;// utilizada para debug
	semaforoAleatorio=0;
	vecesSecuencia=0;
	vecesAleatorio=0;
	contadorPlayer=0;
	incRand=0;
	modoAudio=0;
	puntos=0;
	aumentaPuntos=3;
	contSecuencia=0;
	bucleSecuencia=0;
	vecesSecuencia=0;
	//Modos 
	modo_menuMain=true;
	game=false;
	game40=false;
	game50=false;
	game80=false;
	modo_secuencia_colores=false;
	modo_touch=false;
	modo_color_random=false;
	modo_game_over=false;
	game_over=false;
	custom_wait_touch=true;
	modo_blue=false;
	button_back=false;
	activarBoton=false;
	firstTime=true;
	firstTimeMSC=true;
	generaSaveGameFlag=false;
	modo_input_player=false;
	salir=false;
	semaforo=true;	
}
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
bool comparaStr (char entrada[],char modelo[]){
int ind = 0;

while (entrada[ind]!='\0' && modelo[ind]!='\0' && entrada[ind] == modelo[ind]) ind++;

if (entrada[ind]!='\0' || modelo[ind]!='\0')
   return false;

return true;
}
void secuenciaColores(){
// Secuencia de colores. El contador va de 0 a 3 y se resetea
	if(semaforo)
	{	if(bucleSecuencia%2==0)
		{
			if(contSecuencia==0)
			{
				color='G';
				contSecuencia++;
			}
			else if(contSecuencia==1)
			{
			color='R';
			contSecuencia++;
			}
			else if(contSecuencia==2)
			{
			color='B';
			contSecuencia++;
			}
			else if(contSecuencia==3)
			{
			color='Y';
			contSecuencia++;
			contSecuencia=0;
			}
			
			if(bucleSecuencia==4)
			{
				bucleSecuencia=0;
			}
		}
		bucleSecuencia++;
	}
	
	if(vecesSecuencia==8)
	{
		semaforo=false;
		color=' ';
	}
	vecesSecuencia++;
}
void fcGameOver(){

	modo_color_random=false;
	modo_menuMain=true;
	modo_juego=false;
	modo_touch=false;
	modo_game_over=false;
	game_over=false;
	firstTime=true;
	firstTimeMSC=true;
	game=false;
	game40=false;
	game50=false;
	modo_secuencia_colores=false;
	custom_wait_touch=true;
	modo_input_player=false;
	semaforo=true;
	
	vecesAleatorio=0;
	contadorPlayer=0;
	contSemaforoColorOnOff=0;
	semaforoAleatorio=0;
	contGameOver=0;
	puntos=0;
}
oid marcador(){
		char cadena[3];
		int digito1;
		int digito0;
		if(puntos<10){
			renderTexture(numerosColoresTxt.texture, renderer, 0, 0, 1020, 50, 100, 100);//0
			renderTexture(numerosColoresTxt.texture, renderer, 0+puntos*95, 0, 1120, 50, 95, 100);//
		}else{
			itoa(puntos, cadena, 10);
			digito0=cadena[1]-48;
			digito1=cadena[0]-48;
			renderTexture(numerosColoresTxt.texture, renderer, 0+digito0*95, 0, 1120, 50, 95, 100);//
			renderTexture(numerosColoresTxt.texture, renderer, 0+digito1*95, 0, 1020, 50, 95, 100);//
		}
}
void limpiaArrayColores(){				
	for (t=0;t<99;t++){
		arrayColores[t]='\0';	
	}
}
