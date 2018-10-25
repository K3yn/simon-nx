#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <switch.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "mydebug.h"
#include "SDL_helper.h"
#include "simon_touch.h"
#include "simon_helper.h"
#include "simon_savegame.h"
#include "simon_textures.h"
#include "simon_acc.h"
#include "simon_fonts.h"
u32 kDown;
u32 kHeld;
u32 kUp;
u8 contMenuMain;// 
u8 contMenuModos;// 
u8 saved_selector;


bool modo_menuMain;

bool modo_juego;
bool selectorModo;
bool game;
bool game50;
bool modo_color_random;
bool modo_secuencia_colores;
bool modo_game_over;
bool modo_input_player;
bool game_over;
bool modo_touch;
bool modo_highScores;
bool modo_blue;		
bool data_changed;
bool generaSaveGameFlag;
bool button_back;
bool activarBoton;
bool firstTime;
bool firstTimeMSC;
bool salir;
bool semaforo;
int contGameOver;
int numAleatorio;
int semaforoAleatorio;
int contSemaforoSecColores; 
int contSemaforoColorOnOff;
int vecesAleatorio;
int contadorPlayer;
int puntos;
int aumentaPuntos;
int contSecuencia;
int bucleSecuencia;
int posEnArray;
int t;
int vecesSecuencia;

char arrayColores[99];
char color;
char chHighscore0[3];
char chHighscore1[3];
char chHighscore2[3];
int idUsuario;


bool comparaStr (char entrada[],char modelo[])
{
int ind = 0;

while (entrada[ind]!='\0' && modelo[ind]!='\0' && entrada[ind] == modelo[ind]) ind++;

if (entrada[ind]!='\0' || modelo[ind]!='\0')
   return false;

return true;
}
void secuenciaColores(){
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
	SDL_Delay(2000);
	modo_color_random=false;
	modo_menuMain=true;
	modo_juego=false;
	modo_touch=false;
	modo_game_over=false;
	game_over=false;
	firstTime=true;
	firstTimeMSC=true;
	game=false;
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

void marcador(){
		char cadena[3];
		int digito1;
		int digito0;
		if(puntos<10){
			renderTexture(numerosColoresTxt.texture, renderer, 0, 0, 1000, 50, 100, 100);//0
			renderTexture(numerosColoresTxt.texture, renderer, 0+puntos*95, 0, 1100, 50, 95, 100);//
		}else{
			itoa(puntos, cadena, 10);
			digito0=cadena[1]-48;
			digito1=cadena[0]-48;
			renderTexture(numerosColoresTxt.texture, renderer, 0+digito0*95, 0, 1100, 50, 95, 100);//
			renderTexture(numerosColoresTxt.texture, renderer, 0+digito1*95, 0, 1000, 50, 95, 100);//
		}
}

void newHighscore(){
		
		FILE* save = fopen(filename, "wb");
		if (save)
		{ 
			fwrite(highscore, sizeof(u16), 3, save);
			fwrite(namePlayer, sizeof(u64), 4, save);
			fclose(save);
		}
}

void limpiaArrayColores(){
	for (t=0;t<99;t++){
		arrayColores[t]='\0';	
	}
}

// GO

void displayJuego(){
	SDL_RenderClear(renderer);
	SDL_DrawRect(renderer,0,0,1280,768,WHITE);
	SDL_DrawText(renderer, Roboto_60, 40, 55, GRAY, "SIMON - ");//
	SDL_DrawText(renderer, Roboto_60, 275, 55, RED, "NX");//
	SDL_DrawImageScale(icon.texture, 20, 600, 96, 96);
	SDL_DrawImageScale(iconframe.texture, 20, 600, 96, 96);
	SDL_DrawText(renderer, Roboto_large, 130, 630, BLACK, username);
	renderTexture(bgCircle.texture, renderer, 0, 0, 285, 20, 696, 696);// Circle
	if(modo_menuMain){
		renderTexture(colorM4_off[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green_off
		SDL_DrawText(renderer, Roboto_large, 585, 100, GRAY, "PLAY");
		renderTexture(colorM4_off[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red_off
		SDL_DrawText(renderer, Roboto_large, 845, 360, GRAY, "EXIT");
		renderTexture(colorM4_off[2].texture, renderer, 0, 0, 302, 145, 201, 436);//yellow_off
		SDL_DrawText(renderer, Roboto_large, 320, 360, GRAY, "SCORES");
		renderTexture(colorM4_off[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue_off
		SDL_DrawText(renderer, Roboto_large, 555, 600, GRAY, "CREDITS");
		switch(contMenuMain){
			case 0:// PLAY - GREEN
				renderTexture(colorM4_on[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
				SDL_DrawText(renderer, Roboto_large, 585, 100, WHITE, "PLAY");
				break;
			case 1:// EXIT - RED  
				renderTexture(colorM4_on[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red
				SDL_DrawText(renderer, Roboto_large, 845, 360, WHITE, "EXIT");
				break;
			case 2:// SCORES -  YELLOW
				renderTexture(colorM4_on[2].texture, renderer, 0, 0, 302, 145, 201, 436);//yellow
				SDL_DrawText(renderer, Roboto_large, 320, 360, WHITE, "SCORES");
				break;
			case 3://  CREDITS - BLUE
				renderTexture(colorM4_on[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
				SDL_DrawText(renderer, Roboto_large, 555, 600, WHITE, "CREDITS");
				break;					
			default:
				break;
		}
		SDL_DrawText(renderer, Roboto, 20, 600, BLACK, errorAccount);
		SDL_DrawText(renderer, Roboto_large, 585, 80, WHITE, dbgRC);
	}
	else if(modo_juego)
	{
		if(selectorModo)
		{	
			renderTexture(colorM3_off[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
			renderTexture(colorM3_off[1].texture, renderer, 0, 0, 692, 293, 276, 386);//red
			renderTexture(colorM3_off[2].texture, renderer, 0, 0, 300, 293, 276, 386);//blue
			SDL_DrawText(renderer, Roboto_large, 585, 100, GRAY, "EASY");
			SDL_DrawText(renderer, Roboto_large, 810, 440, GRAY, "BACK");
			SDL_DrawText(renderer, Roboto_large, 340, 440, GRAY, "MEDIUM");
	
			switch(contMenuModos){
				case 0:// PLAY - GREEN
					renderTexture(colorM3_on[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
					SDL_DrawText(renderer, Roboto_large, 585, 100, WHITE, "EASY");
					break;
				case 1:// EXIT - RED  
					renderTexture(colorM3_on[1].texture, renderer, 0, 0, 692, 293, 276, 386);//red
					SDL_DrawText(renderer, Roboto_large, 810, 440, WHITE, "BACK");
					break;
				case 2://  CREDITS - BLUE
					renderTexture(colorM3_on[2].texture, renderer, 0, 0, 300, 293, 276, 386);//blue
					SDL_DrawText(renderer, Roboto_large, 340, 440, WHITE, "MEDIUM");
					break;					
				default:
					break;
			}
		}
		else if(game)
		{
			renderTexture(colorM4_off[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
			renderTexture(colorM4_off[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red
			renderTexture(colorM4_off[2].texture, renderer, 0, 0, 302, 145, 201, 436);//yellow
			renderTexture(colorM4_off[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
			
			if(modo_input_player)
			{
				renderTexture(joyconTxt.texture, renderer, 0, 0, 980, 400, 256, 256);
				
			}
			if(modo_secuencia_colores || modo_color_random)
			{
				renderTexture(loop.texture, renderer, 0, 0, 980, 400, 256, 256);
			}
			if(modo_game_over){
				SDL_DrawText(renderer, Roboto_large, 530, 330, WHITE, "GAME OVER");
			}
			
		}
		else if(game50)
		{
			renderTexture(colorM5_off[0].texture, renderer, 0, 0, 460, 35, 349, 162);//green
			renderTexture(colorM5_off[1].texture, renderer, 0, 0, 767, 115, 196, 336);//red
			renderTexture(colorM5_off[2].texture, renderer, 0, 0, 325, 443, 296, 234);//blue
			renderTexture(colorM5_off[3].texture, renderer, 0, 0, 645, 443, 296, 234);//pink
			renderTexture(colorM5_off[4].texture, renderer, 0, 0, 305, 115, 196, 337);//yellow
			if(modo_input_player)
			{
				renderTexture(joyconTxt.texture, renderer, 0, 0, 980, 400, 256, 256);
				
			}
			if(modo_secuencia_colores || modo_color_random)
			{
				renderTexture(loop.texture, renderer, 0, 0, 980, 400, 256, 256);
			}
			if(modo_game_over){
				SDL_DrawText(renderer, Roboto_large, 530, 330, WHITE, "GAME OVER");
			}
			
		}


		if(game || modo_input_player || modo_color_random || modo_game_over)
		{
			marcador();
		}
		//SDL_DrawText(renderer, Roboto_large, 130, 680, BLACK, arrayColores);	
	}
	else if(modo_highScores)
	{	
		renderTexture(bgSquare.texture, renderer, 0, 0, 130, 143, 1012, 436);
		renderTexture(colorM4_off[2].texture, renderer, 0, 0, 130, 145, 201, 436);//yellow_off
		renderTexture(colorM4_off[1].texture, renderer, 0, 0, 940, 145, 201, 436);//red_off
		SDL_DrawText(renderer, Roboto_large, 1010, 360, GRAY, "BACK");
		if(button_back)
		{
			renderTexture(colorM4_on[1].texture, renderer, 0, 0, 940, 145, 201, 436);//red_on
			SDL_DrawText(renderer, Roboto_large, 1010, 360, WHITE, "BACK");
		}
		renderTexture(bgCircle.texture, renderer, 0, 0, 285, 20, 696, 696);// Circle
		renderTexture(colorM4_off[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
		renderTexture(colorM4_off[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
		
		SDL_DrawText(renderer, Roboto_50, 540, 100, WHITE, "SCORES");
		
		SDL_DrawText(renderer, Roboto_large, 470, 275, WHITE, namePlayer[0]);
		SDL_DrawText(renderer, Roboto_large, 760, 275, WHITE, chHighscore0);
		
		SDL_DrawText(renderer, Roboto_large, 470, 355, WHITE, namePlayer[1]);
		SDL_DrawText(renderer, Roboto_large, 760, 355, WHITE, chHighscore1);
		
		SDL_DrawText(renderer, Roboto_large, 470, 435, WHITE, namePlayer[2]);
		SDL_DrawText(renderer, Roboto_large, 760, 435, WHITE, chHighscore2);	

	}
	else if(modo_blue)
	{	
		renderTexture(bgSquare.texture, renderer, 0, 0, 130, 143, 1012, 436);
		renderTexture(colorM4_off[2].texture, renderer, 0, 0, 130, 145, 201, 436);//yellow_off
		renderTexture(colorM4_off[1].texture, renderer, 0, 0, 940, 145, 201, 436);//red_off
		SDL_DrawText(renderer, Roboto_large, 1010, 360, GRAY, "BACK");
		if(button_back)
		{
			renderTexture(colorM4_on[1].texture, renderer, 0, 0, 940, 145, 201, 436);//red_on
			SDL_DrawText(renderer, Roboto_large, 1010, 360, WHITE, "BACK");
		}
		renderTexture(bgCircle.texture, renderer, 0, 0, 285, 20, 696, 696);// Circle
		renderTexture(colorM4_off[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
		renderTexture(colorM4_off[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
		SDL_DrawText(renderer, Roboto_50, 540, 100, WHITE, "CREDITS");
		
		switch(color)
		{
				case 'G':
					renderTexture(colorM4_on[0].texture, renderer, 0, 0, 415, 35, 437, 202);
					break;
				case 'R':
					renderTexture(colorM4_on[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red
					break;
				case 'Y':
					renderTexture(colorM4_on[2].texture, renderer, 0, 0, 302, 145, 201, 436);
					break;
				case 'B':
					renderTexture(colorM4_on[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
					break;
				default:
					break;	
		}
	}
	// Printamos el valor de color
		switch(color){
			case 'G':
				renderTexture(colorM4_on[0].texture, renderer, 0, 0, 415, 35, 437, 202);
				break;
			case 'R':
				renderTexture(colorM4_on[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red
				break;
			case 'Y':
				renderTexture(colorM4_on[2].texture, renderer, 0, 0, 302, 145, 201, 436);
				break;
			case 'B':
				renderTexture(colorM4_on[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
				break;
			default:
				break;	
		}
	SDL_RenderPresent(renderer);			
}
void manejaControles()
{
		if(modo_menuMain)
		{
			// Si se pulsa abajo
			if (kDown & KEY_DOWN)
			{
				contMenuMain = 3;
				playSound('N');
			}
			// Si se pulsa arriba 
			else if (kDown & KEY_UP)
			{
				contMenuMain = 0;
				playSound('N');
			}
			// Si se pulsa arriba 
			else if (kDown & KEY_RIGHT)
			{
				contMenuMain = 1;
				playSound('N');
			}
			// Si se pulsa arriba 
			else if (kDown & KEY_LEFT)
			{
				contMenuMain = 2;
				playSound('N');
			}
			// SI PULSAMOS LA A
			// Si se pulsa A entramos al juego
			else if((kUp & KEY_A) && (contMenuMain==0))
			{
					modo_menuMain=false;
					modo_juego=true;
					selectorModo=true;
			}
			// Si se pulsa Y entramos en la parte de highscores
			else if((kUp & KEY_A) && (contMenuMain==2))
			{
				modo_menuMain=false;
				modo_highScores=true;

			}
			// Si se pulsa B
			else if((kUp & KEY_A) && (contMenuMain==1))
			{
				playSound('X');
				salir=true;// SALIMOS
			}
			// Si se pulsa B
			else if((kUp & KEY_A) && (contMenuMain==3))
			{
				modo_blue=true;
				modo_menuMain=false;
			}			

			// TACTIL
			// comenzamos el juego con el green
			u8 newContMenuMain;
			if ((kDown & KEY_TOUCH && inBox(Stylus, 505, 65, 785, 200)))//green
			{
				newContMenuMain=0;
				playSound('N');
				if (contMenuMain == newContMenuMain)
				{
					modo_menuMain=false;
					modo_juego=true;
					selectorModo=true;
					//modo_color_random=true;
				}
				else
				{
					contMenuMain = newContMenuMain;
				}
			}// salir
			else if ((kDown & KEY_TOUCH && inBox(Stylus, 800, 220, 940, 500)))//red
			{
				newContMenuMain=1;
				
				if (contMenuMain == newContMenuMain)
				{
					playSound('N');
					salir=true;

				}
				else
				{
					playSound('N');
					contMenuMain = newContMenuMain;
				}
			}// creditos
			else if ((kDown & KEY_TOUCH && inBox(Stylus, 340, 220, 480, 500)))//yellow
			{
				newContMenuMain=2;
				
				if (contMenuMain == newContMenuMain)
				{
					modo_menuMain=false;
					modo_highScores=true;
					playSound('P');
				}
				else
				{
					playSound('N');
					contMenuMain = newContMenuMain;
				}
			}		
			else if ((kDown & KEY_TOUCH && inBox(Stylus, 526, 520, 753, 655)))//blue
			{
				newContMenuMain=3;
				
				if (contMenuMain == newContMenuMain)
				{
					modo_menuMain=false;
					modo_blue=true;
					playSound('P');
				}
				else
				{
					playSound('N');
					contMenuMain = newContMenuMain;
				}
			}
		}
		else if(modo_juego)
		{	
			if(selectorModo)
			{
				// Si se pulsa abajo
				if (kDown & KEY_DOWN)
				{
					//contMenuModos = 2;
					//playSound('N');
				}
				// Si se pulsa arriba 
				else if (kDown & KEY_UP)
				{
					contMenuModos = 0;
					playSound('N');
				}
				// Si se pulsa arriba 
				else if (kDown & KEY_RIGHT)
				{
					contMenuModos = 1;
					playSound('N');
				}
				// Si se pulsa arriba 
				else if (kDown & KEY_LEFT)
				{
					contMenuModos = 2;
					playSound('N');
				}
				// SI PULSAMOS LA A
				// Si se pulsa A entramos al juego
				else if((kUp & KEY_A) && (contMenuModos==0))
				{
						selectorModo=false;
						modo_juego=true;
						game=true;
						modo_color_random=true;
					
				}
				// Si se pulsa Y entramos en la parte de highscores
				else if((kUp & KEY_A) && (contMenuModos==2))
				{
					//modo_menuMain=false;
					//modo_highScores=true;

				}
				// Si se pulsa 
				else if((kUp & KEY_A) && (contMenuModos==1))
				{
					selectorModo=false;
					modo_menuMain=true;
				}
				// Si se pulsa B
				else if((kUp & KEY_A) && (contMenuModos==3))
				{
					//modo_blue=true;
					//modo_menuMain=false;
				}			


				u8 newContMenuModos;
				if ((kDown & KEY_TOUCH && inBox(Stylus, 505, 65, 785, 200)))//green
				{
					newContMenuModos=0;
					playSound('N');
					if (contMenuModos == newContMenuModos)
					{
						selectorModo=false;
						modo_juego=true;
						game=true;
						modo_color_random=true;
					}
					else
					{
						contMenuModos = newContMenuModos;
					}
				}// salir
				else if ((kDown & KEY_TOUCH && inBox(Stylus, 780, 260, 920, 560)))//red
				{
					newContMenuModos=1;
					
					if (contMenuModos == newContMenuModos)
					{
						playSound('P');
						modo_menuMain=true;
						selectorModo=false;
						modo_juego=false;
					}
					else
					{
						playSound('N');
						contMenuModos = newContMenuModos;
					}
				}// 

				else if ((kDown & KEY_TOUCH && inBox(Stylus,  340, 220, 480, 500)))//blue
				{
					newContMenuModos=2;
					
					if (contMenuModos == newContMenuModos)
					{
						selectorModo=false;
						modo_juego=true;
						game50=true;
						modo_color_random=true;
						playSound('P');
					}
					else
					{
						playSound('N');
						contMenuModos = newContMenuModos;
					}
				}	
			}
			if(modo_input_player)
			{
				// AL PRESIONAR EL TACTIL
				if(kUp & KEY_TOUCH)
				{
				color=' ';
				}			
				if (kDown & KEY_TOUCH)
				{
					if (inBox(Stylus, 505, 65, 785, 200))//green
					{
						
						color='G';
						playSound('G');
						if(arrayColores[contadorPlayer]=='G'){
							if(contadorPlayer==strlen(arrayColores)-1){
								game=true;
								modo_secuencia_colores=true;
								modo_input_player=false;
								modo_touch=true;
								puntos=puntos+aumentaPuntos;
								firstTimeMSC=true;
							}
							contadorPlayer++;
						}
						else{
							game=true;
							playSound('X');
							modo_game_over=true;
						}
					}
					else if (inBox(Stylus, 526, 520, 753, 655))//blue
					{
						color='B';
						playSound('B');
						if(arrayColores[contadorPlayer]=='B'){
							if(contadorPlayer==strlen(arrayColores)-1){
								game=true;
								modo_secuencia_colores=true;
								modo_input_player=false;
								modo_touch=true;
								puntos=puntos+aumentaPuntos;
								firstTimeMSC=true;
							}
							contadorPlayer++;
						}
						else{
							game=true;
							playSound('X');
							modo_game_over=true;
						}
					}	
					else if (inBox(Stylus, 340, 220, 480, 500))//Yellow
					{
						color='Y';
						playSound('Y');
						if(arrayColores[contadorPlayer]=='Y'){
							if(contadorPlayer==strlen(arrayColores)-1){
								game=true;
								modo_secuencia_colores=true;
								modo_input_player=false;
								modo_touch=true;
								puntos=puntos+aumentaPuntos;
								firstTimeMSC=true;
							}
							contadorPlayer++;
						}
						else{
							game=true;
							playSound('X');
							modo_game_over=true;
						}
							
							
					}
					else if (inBox(Stylus, 800, 220, 940, 500))//Red
					{
						color='R';
						playSound('R');
						if(arrayColores[contadorPlayer]=='R'){
							if(contadorPlayer==strlen(arrayColores)-1){
								game=true;
								modo_secuencia_colores=true;
								modo_input_player=false;
								modo_touch=true;
								puntos=puntos+aumentaPuntos;
								firstTimeMSC=true;
							}
							contadorPlayer++;
						}
						else{
							game=true;
							playSound('X');
							modo_game_over=true;
							
						}
					}				
				}
				// Al PRESIONAR LAS TECLAS
				if(kDown & KEY_X){
					color='G';
					playSound('G');
				}		
				else if(kDown & KEY_Y){
					color='Y';
					playSound('Y');
				}
				else if(kDown & KEY_A){
					color='R';
					playSound('R');
				}
				else if(kDown & KEY_B){
					color='B';
					playSound('B');
				}
				// al soltar la tecla
				if(kUp & KEY_X){
					color=' ';
					if(arrayColores[contadorPlayer]=='G'){
						if(contadorPlayer==strlen(arrayColores)-1){
							game=true;
							modo_secuencia_colores=true;
							modo_input_player=false;
							modo_touch=true;
							puntos=puntos+aumentaPuntos;
							firstTimeMSC=true;
						}
						contadorPlayer++;
					}
					else
					{
						game=true;
						playSound('X');
						modo_game_over=true;
					}
				}
				else if(kUp & KEY_Y){
					color=' ';
					if(arrayColores[contadorPlayer]=='Y'){
						if(contadorPlayer==strlen(arrayColores)-1){
							game=true;
							modo_secuencia_colores=true;
							modo_input_player=false;
							modo_touch=true;
							puntos=puntos+aumentaPuntos;
							firstTimeMSC=true;
						}
						contadorPlayer++;
					}
					else{
						game=true;
						playSound('X');
						modo_game_over=true;
					}				
				}
				else if(kUp & KEY_A){
					color=' ';
					if(arrayColores[contadorPlayer]=='R'){
						if(contadorPlayer==strlen(arrayColores)-1){
							game=true;
							modo_secuencia_colores=true;
							modo_input_player=false;
							modo_touch=true;
							puntos=puntos+aumentaPuntos;
							firstTimeMSC=true;
						}
						contadorPlayer++;
					}
					else{
						game=true;
						playSound('X');
						modo_game_over=true;
						
					}			
				}
				else if(kUp & KEY_B){
					color=' ';
					if(arrayColores[contadorPlayer]=='B'){
						if(contadorPlayer==strlen(arrayColores)-1){
							game=true;
							modo_secuencia_colores=true;
							modo_input_player=false;
							modo_touch=true;
							puntos=puntos+aumentaPuntos;
							firstTimeMSC=true;
						}
						contadorPlayer++;
					}
					else{
						game=true;
						playSound('X');
						modo_game_over=true;
					}
				}
				// SALIMOS
				else if(kDown & KEY_L){
					fcGameOver();limpiaArrayColores();
				}
			}
			if(game)
			{
				if(modo_color_random){
					if(firstTime){
						SDL_Delay(1500);
						playSound('S');
						firstTime=false;
					}
					if(semaforoAleatorio==0){

						semaforoAleatorio++;
					}
					else if(semaforoAleatorio==1)
					{
						
						numAleatorio = rand() % 4;
						switch(numAleatorio){
							case 0:
								//GREEN
								color='G';
								arrayColores[vecesAleatorio]='G';
								break;
							case 1:
								//RED 
								color='R';
								arrayColores[vecesAleatorio]='R';
								break;
							case 2:
								//YELLOW
								color='Y';
								arrayColores[vecesAleatorio]='Y';
								break;
							case 3:
								//BLUE
								color='B';
								arrayColores[vecesAleatorio]='B';
								break;
							default:
								break;
							
						}
					
					vecesAleatorio++;
					semaforoAleatorio++;
					playSound(color);// 
					}
					else if(semaforoAleatorio==2)
					{
						color=' ';
						modo_input_player=true;
						semaforoAleatorio=0;
						modo_color_random=false;
						SDL_Delay(300);
						contadorPlayer=0;
					}
				}
				else if(modo_secuencia_colores)
				{

					if(!modo_touch){
						if(contSemaforoSecColores<strlen(arrayColores)){
							//si entro la primera vez
							if(contSemaforoSecColores==0){
					
							}
							if(contSemaforoColorOnOff==0){
								color=' ';
								contSemaforoColorOnOff++;
								
							}
							else if(contSemaforoColorOnOff==1){				
								if(firstTimeMSC){
									SDL_Delay(1500);
									firstTimeMSC=false;
								}
								color=arrayColores[contSemaforoSecColores];
								playSound(color);
								contSemaforoColorOnOff++;
							}
							else if(contSemaforoColorOnOff==2){
								
								color=' ';
								contSemaforoColorOnOff=0;
								contSemaforoSecColores++;
							}
							
						}
						else if(contSemaforoSecColores==strlen(arrayColores)){
							contSemaforoSecColores=0;
							modo_secuencia_colores=false;
							modo_color_random=true;
							
						}
					}
					modo_touch=false;
				}
				else if(modo_game_over){
					
					if (contGameOver==0){
						game_over=false;
					}
					else if(contGameOver==1)
					{
						game_over=true;
					}
					else if(contGameOver==2)
					{
						color=' ';
						SDL_Delay(1000);

						limpiaArrayColores();
						if(!userAnonymous)
						{
							
							if(puntos>highscore[0])
							{
								if(comparaStr(namePlayer[0],username)==0)
								{

									strcpy(namePlayer[2],namePlayer[1]);
									strcpy(namePlayer[1],namePlayer[0]);
									
									//
									highscore[2]=highscore[1];
									highscore[1]=highscore[0];

									stpcpy(namePlayer[0],username);
									highscore[0]=puntos;
									
								}
								if(comparaStr(namePlayer[0],username)==1)
								{

									stpcpy(namePlayer[0],username);
									highscore[0]=puntos;
									
								}
								newHighscore();

							}
							else if(puntos>highscore[1])
							{
								if(comparaStr(namePlayer[1],username)==1)
								{
									
									highscore[2]=highscore[1];
									stpcpy(namePlayer[2],namePlayer[1]);
									stpcpy(namePlayer[1],username);
									highscore[2]=highscore[1];
									highscore[1]=puntos;
									
								}
								newHighscore();
							}
							else if(puntos>highscore[2])
							{
								if(comparaStr(namePlayer[1],username)==0 || comparaStr(namePlayer[0],username)==0)
								{
									stpcpy(namePlayer[2],username);
									highscore[2]=puntos;
								}
								newHighscore();
							}
						}	
					fcGameOver();
					}
					contGameOver++;
				}
			}
		}
		else if(modo_highScores)
		{
			// Si 
			
			if(kUp & KEY_B){
				modo_highScores=false;
				modo_menuMain=true;
			}
			// salir tactil
			if ((kDown & KEY_TOUCH && inBox(Stylus, 900, 220, 1101, 500)))//red
			{
				if (!activarBoton)
				{
						button_back=true;
						activarBoton=true;
						playSound('N');
				}
				else
				{
						activarBoton=false;
						button_back=false;
						modo_highScores=false;
						modo_menuMain=true;
						playSound('P');
				}
			}	
			itoa(highscore[0],chHighscore0,10);
			itoa(highscore[1],chHighscore1,10);
			itoa(highscore[2],chHighscore2,10);
		}
		else if(modo_blue)
		{
			if(kUp & KEY_B){
				modo_highScores=false;
				modo_menuMain=true;
			}
			// salir tactil
			if ((kDown & KEY_TOUCH && inBox(Stylus, 900, 220, 1101, 500)))//red
			{
				if (!activarBoton)
				{
						button_back=true;
						activarBoton=true;
						playSound('N');
				}
				else
				{
						activarBoton=false;
						button_back=false;
						modo_highScores=false;
						modo_menuMain=true;
						playSound('P');
				}
			}	
		 secuenciaColores();
		}
}

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	SDL_Init(SDL_INIT_AUDIO);
	romfsInit();
	TTF_Init();
	srand (time(NULL));

	window = SDL_CreateWindow("Main-Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);	
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);	

	contMenuMain=4;
	contMenuModos=3;
	numAleatorio=0;
	contSemaforoSecColores=0;
	contSemaforoColorOnOff=0;
	contGameOver=0;
	t=0;// utilizada para debug
	semaforoAleatorio=0;
	posEnArray=0;
	vecesSecuencia=0;
	vecesAleatorio=0;
	contadorPlayer=0;
	puntos=0;
	aumentaPuntos=3;
	contSecuencia=0;
	bucleSecuencia=0;
	vecesSecuencia=0;
	//Modos 
	modo_menuMain=true;
	game=false;
	game50=false;
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
	if(leeSaveGame()){
		generaSaveGame();
		leeSaveGame();
	}
	getUserInfo(0); 
	load_textures();

	saved_selector = contMenuMain;
	data_changed = false;

	// Main loop
    while(appletMainLoop())
    {   

        hidScanInput();
		hidTouchRead(&Stylus, 0);
		
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		kUp = hidKeysUp(CONTROLLER_P1_AUTO);
		kHeld= hidKeysHeld(CONTROLLER_P1_AUTO);
        if (kDown & KEY_PLUS || salir) break; // break in order to return to hbmenu
		
		manejaControles();		
		displayJuego();

    }

	SDL_Quit();
    return 0;
}

