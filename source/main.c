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

//#include "mydebug.h"
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

void displayJuego(){
	SDL_RenderClear(renderer);
	SDL_DrawRect(renderer,0,0,1280,768,WHITE);
	SDL_DrawText(renderer, Roboto_60, 40, 55, GRAY, "SIMON - ");//
	SDL_DrawText(renderer, Roboto_60, 275, 55, RED, "NX");//
	SDL_DrawImageScale(icon.texture, 20, 600, 96, 96);
	SDL_DrawImageScale(iconframe.texture, 20, 600, 96, 96);
	SDL_DrawText(renderer, Roboto_large, 130, 630, BLACK, username);
	renderTexture(bgCircle.texture, renderer, 0, 0, 285, 20, 696, 696);//
	if(modo_menuMain){
		//
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
			SDL_DrawText(renderer, Roboto_large, 810, 440, GRAY, "HARD");
			SDL_DrawText(renderer, Roboto_large, 340, 440, GRAY, "MEDIUM");
	
			switch(contMenuModos){
				case 0:// PLAY - GREEN
					renderTexture(colorM3_on[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
					SDL_DrawText(renderer, Roboto_large, 585, 100, WHITE, "EASY");
					break;
				case 1:// EXIT - RED  
					renderTexture(colorM3_on[1].texture, renderer, 0, 0, 692, 293, 276, 386);//red
					SDL_DrawText(renderer, Roboto_large, 810, 440, WHITE, "HARD");
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
			if(game40)
			{
				//
				renderTexture(colorM4_off[0].texture, renderer, 0, 0, 415, 35, 437, 202);//green
				renderTexture(colorM4_off[1].texture, renderer, 0, 0, 765, 145, 201, 436);//red
				renderTexture(colorM4_off[2].texture, renderer, 0, 0, 302, 145, 201, 436);//yellow
				renderTexture(colorM4_off[3].texture, renderer, 0, 0, 415, 493, 437, 202);//blue
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
			else if(game50)
			{
				// 
				renderTexture(colorM5_off[0].texture, renderer, 0, 0, 460, 35, 349, 162);//green
				renderTexture(colorM5_off[1].texture, renderer, 0, 0, 767, 115, 196, 336);//red
				renderTexture(colorM5_off[2].texture, renderer, 0, 0, 305, 115, 196, 337);//yellow
				renderTexture(colorM5_off[3].texture, renderer, 0, 0, 325, 443, 296, 234);//blue
				renderTexture(colorM5_off[4].texture, renderer, 0, 0, 645, 443, 296, 234);//pink
				
				switch(color)
				{
					case 'G':
						renderTexture(colorM5_on[0].texture, renderer, 0, 0, 460, 35, 349, 162);//green
						break;
					case 'R':
						renderTexture(colorM5_on[1].texture, renderer, 0, 0, 767, 115, 196, 336);//red
						break;
					case 'Y':
						renderTexture(colorM5_on[2].texture, renderer, 0, 0, 305, 115, 196, 337);//yellow
						break;						
					case 'B':
						renderTexture(colorM5_on[3].texture, renderer, 0, 0, 325, 443, 296, 234);//blue
						break;
					case 'P':
						renderTexture(colorM5_on[4].texture, renderer, 0, 0, 645, 443, 296, 234);//pink
						break;
					default:
						break;	
				}
			}
			else if(game80)
			{
				// 
				renderTexture(colorM8_off[0].texture, renderer, 0, 0, 410, 35, 204, 202);//green
				renderTexture(colorM8_off[1].texture, renderer, 0, 0, 645, 35, 204, 202);//yellow
				renderTexture(colorM8_off[2].texture, renderer, 0, 0, 760, 145, 202, 204);//orange
				renderTexture(colorM8_off[3].texture, renderer, 0, 0, 760, 380, 204, 202);//red
				renderTexture(colorM8_off[4].texture, renderer, 0, 0, 645, 495, 204, 202);//violet
				renderTexture(colorM8_off[5].texture, renderer, 0, 0, 410, 495, 204, 202);//pink
				renderTexture(colorM8_off[6].texture, renderer, 0, 0, 300, 380, 204, 202);//blue
				renderTexture(colorM8_off[7].texture, renderer, 0, 0, 300, 145, 204, 202);//cyan
				
				switch(color)
				{
					case 'G':
						renderTexture(colorM8_on[0].texture, renderer, 0, 0, 410, 35, 204, 202);//green
						break;
					case 'Y':
						renderTexture(colorM8_on[1].texture, renderer, 0, 0, 645, 35, 204, 202);//yellow
						break;
					case 'O':
						renderTexture(colorM8_on[2].texture, renderer, 0, 0, 760, 145, 202, 204);//orange
						break;						
					case 'R':
						renderTexture(colorM8_on[3].texture, renderer, 0, 0, 760, 380, 204, 202);//red
						break;
					case 'V':
						renderTexture(colorM8_on[4].texture, renderer, 0, 0, 645, 495, 204, 202);//violet
						break;
					case 'P':
						renderTexture(colorM8_on[5].texture, renderer, 0, 0, 410, 495, 204, 202);//pink
						break;
					case 'B':
						renderTexture(colorM8_on[6].texture, renderer, 0, 0, 300, 380, 204, 204);//blue
						break;
					case 'C':
						renderTexture(colorM8_on[7].texture, renderer, 0, 0, 300, 145, 204, 202);//cyan
						break;						
					default:
						break;	
				}			
			}			
			marcador();
				
			if(modo_input_player)// 
			{
				renderTexture(joyconTxt.texture, renderer, 0, 0, 980, 400, 256, 256);
			}
			// 
			if(modo_secuencia_colores || modo_color_random)
			{
				renderTexture(loop.texture, renderer, 0, 0, 980, 400, 256, 256);
			}
			if(modo_game_over){
				SDL_DrawText(renderer, Roboto_large, 530, 330, WHITE, "GAME OVER");
				//
			}
		}
		//SDL_DrawText(renderer, Roboto_large, 130, 680, BLACK, arrayColores);//DEBUG
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
		
		switch(color)//
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
	SDL_RenderPresent(renderer);			
}
void manejaControles()
{
		if(modo_menuMain)
		{
			if (kDown & KEY_DOWN)// 
			{
				contMenuMain = 3;
				playSound('N');
			}
			else if (kDown & KEY_UP)//
			{
				contMenuMain = 0;
				playSound('N');
			}
			else if (kDown & KEY_RIGHT)//
			{
				contMenuMain = 1;
				playSound('N');
			}
			else if (kDown & KEY_LEFT)//  
			{
				contMenuMain = 2;
				playSound('N');
			}	 
			else if((kUp & KEY_A) && (contMenuMain==0))//
			{
					modo_menuMain=false;
					modo_juego=true;
					selectorModo=true;
			}
			else if((kUp & KEY_A) && (contMenuMain==2))// 
			{
				modo_menuMain=false;
				modo_highScores=true;
			}
			else if((kUp & KEY_A) && (contMenuMain==1))//
			{
				playSound('X');
				salir=true;// SALIMOS
			}
			else if((kUp & KEY_A) && (contMenuMain==3))//
			{
				modo_blue=true;
				modo_menuMain=false;
			}
			
			//

			u8 newContMenuMain;
			if ((kDown & KEY_TOUCH && inBox(Stylus, 505, 65, 785, 200)))//green
			{
				newContMenuMain=0;
				
				if (contMenuMain == newContMenuMain)
				{
					modo_menuMain=false;
					modo_juego=true;
					selectorModo=true;
					playSound('A');
				}
				else
				{
					playSound('N');
					contMenuMain = newContMenuMain;
				}
			}
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
					playSound('X');
					contMenuMain = newContMenuMain;
				}
			}
			else if ((kDown & KEY_TOUCH && inBox(Stylus, 340, 220, 480, 500)))//yellow
			{
				newContMenuMain=2;
				
				if (contMenuMain == newContMenuMain)
				{
					modo_menuMain=false;
					modo_highScores=true;
					playSound('A');
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
					playSound('A');
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
				if (kDown & KEY_DOWN){}// 
				else if (kDown & KEY_UP)//
				{
					contMenuModos = 0;
					playSound('N');
				}
				else if (kDown & KEY_RIGHT)//
				{
					contMenuModos = 1;
					playSound('N');
				}
				else if (kDown & KEY_LEFT)//
				{
					contMenuModos = 2;
					playSound('N');
				}
				else if((kUp & KEY_A) && (contMenuModos==0))//
				{
					selectorModo=false;
					modo_juego=true;
					game=true;
					game40=true;
					modoAudio=4;
					modo_color_random=true;
					playSound('A');
				}
				else if((kUp & KEY_A) && (contMenuModos==2))//
				{
					playSound('A');
					selectorModo=false;
					modo_juego=true;
					game=true;
					game80=true;
					modoAudio=8;
					modo_color_random=true;
				}
				else if((kUp & KEY_A) && (contMenuModos==3))// 
				{
					selectorModo=false;
					modo_juego=true;
					game=true;
					game50=true;
					modoAudio=5;
					modo_color_random=true;
					playSound('A');
				}				
				//
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
						game40=true;
						modoAudio=4;
						modo_color_random=true;
						playSound('A');
					}
					else
					{
						playSound('N');
						contMenuModos = newContMenuModos;
					}
				}//
				else if ((kDown & KEY_TOUCH && inBox(Stylus, 780, 260, 920, 560)))//red
				{
					newContMenuModos=1;
					
					if (contMenuModos == newContMenuModos)
					{
						playSound('A');
						selectorModo=false;
						modo_juego=true;
						game=true;
						game80=true;
						modoAudio=8;
						modo_color_random=true;
					}
					else
					{
						playSound('N');
						contMenuModos = newContMenuModos;
					}
				}
				else if ((kDown & KEY_TOUCH && inBox(Stylus,  340, 220, 480, 500)))//blue
				{
					newContMenuModos=2;
					
					if (contMenuModos == newContMenuModos)
					{
						selectorModo=false;
						modo_juego=true;
						game=true;
						game50=true;
						modoAudio=5;
						modo_color_random=true;
						playSound('A');
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
				if (kDown & KEY_TOUCH)//
				{
					if (inBox(Stylus, green[0], green[1], green[2], green[3]))//green
					{
						key_touch_player('G');
						color='G';
						playSound('G');
					}
					else if (inBox(Stylus, blue[0], blue[1], blue[2], blue[3]))//blue
					{
						key_touch_player('B');
						color='B';
						playSound('B');
					}	
					else if (inBox(Stylus, yellow[0], yellow[1], yellow[2], yellow[3]))//Yellow
					{
						key_touch_player('Y');
						color='Y';
						playSound('Y');
					}
					else if (inBox(Stylus, red[0], red[1], red[2], red[3]))//Red
					{
						key_touch_player('R');
						color='R';
						playSound('R');
					}
				}
				if(kUp & KEY_TOUCH)// RESET DEL COLOR AL PULSAR EL JUGADOR
				{
				color=' ';
				}			
				if(game40)
				{
					load_vars_touch_colors(0);
					// 
					if(kDown & KEY_X){
						color='G';
						playSound('G');
						key_touch_player('G');
					}		
					else if(kDown & KEY_Y){
						color='Y';
						playSound('Y');
						key_touch_player('Y');
					}
					else if(kDown & KEY_A){
						color='R';
						playSound('R');
						key_touch_player('R');	
					}
					else if(kDown & KEY_B){
						color='B';
						playSound('B');
						key_touch_player('B');
					}
					// 
					if(kUp & KEY_X){
						color=' ';
					}
					else if(kUp & KEY_Y){
						color=' ';	
					}
					else if(kUp & KEY_A){
						color=' ';
					}
					else if(kUp & KEY_B){
						color=' ';
					}
				}
				else if(game50)
				{
					load_vars_touch_colors(1);
					//
					if (kDown & KEY_TOUCH)
					{
						if (inBox(Stylus, pink[0], pink[1], pink[2], pink[3]))
						{
							key_touch_player('P');
							color='P';
							playSound('P');
						}
					}
					// KEYS				
				}
				else if(game80)
				{
					load_vars_touch_colors(2);
					// TOUCH
					if (kDown & KEY_TOUCH)
					{	
						if (inBox(Stylus, pink[0], pink[1], pink[2], pink[3]))// PINK
						{
							key_touch_player('P');
							color='P';
							playSound('P');
						}
						if (inBox(Stylus, orange[0], orange[1], orange[2], orange[3]))// ORANGE
						{
							key_touch_player('O');
							color='O';
							playSound('O');
						}
						if (inBox(Stylus, violet[0], violet[1], violet[2], violet[3]))// VIOLET
						{
							key_touch_player('V');
							color='V';
							playSound('V');
						}									
						if (inBox(Stylus, cyan[0], cyan[1], cyan[2], cyan[3]))// CYAN
						{
							key_touch_player('C');
							color='C';
							playSound('C');
						}				
					}
					// KEYS
					if(kHeld & KEY_DOWN){
						contColorM8++;
						contColorM8 %= 8;
					}
					if(kHeld & KEY_UP){
						if (contColorM8 > 0)
						{
							contColorM8--;
						}
						else
						{
							contColorM8 = 7;
						}
						
					}
					switch(contColorM8){
							case 0:
								color='G';
								break;
							case 1:
								color='Y';
								break;
							case 2:
								color='O';
								break;
							case 3:
								color='R';
								break;
							case 4:
								color='V';
								break;
							case 5:
								color='P';
								break;
							case 6:
								color='B';
								break;
							case 7:
								color='C';
								break;								
							default:
								break;
						}
					if(contColorM8>7){
					contColorM8=0;
					}					
					
					if(kDown & KEY_A){
						if(contColorM8!=-1){
							itoa(contColorM8, intToCharSound,10);
							playSound(intToCharSound[0]);
								switch(contColorM8){
									case 0:
										key_touch_player('G');
										break;
									case 1:
										key_touch_player('Y');
										break;
									case 2:
										key_touch_player('O');
										break;
									case 3:
										key_touch_player('R');
										break;
									case 4:
										key_touch_player('V');
										break;
									case 5:
										key_touch_player('P');
										break;
									case 6:
										key_touch_player('B');
										break;
									case 7:
										key_touch_player('C');
										break;									
									default:
										break;
								}
							contColorM8=-1;
						}
					}
					if(kUp & KEY_A){
						color=' ';
					}	
				}				
				if(kUp & KEY_L){// Salida enmedio del juego en cualquier modo
					fcGameOver();
				}		
			}
			if(game)
			{
				if(modo_color_random){
					
					if(semaforoAleatorio==0){
						semaforoAleatorio++;//SDL_Delay(300);//
					}
					else if(semaforoAleatorio==1)
					{
						if(firstTime){
							SDL_Delay(1500);//
							playSound('S');
							firstTime=false;
						}
						if(game40){incRand=4;}
						else if(game50){incRand=5;}
						else if(game80){incRand=8;}
						numAleatorio = rand() % incRand;
						switch(numAleatorio){
							case 0:
								//GREEN
								color='G';
								arrayColores[vecesAleatorio]='G';
								break;
							case 1:
								//YELLOW 
								color='Y';
								arrayColores[vecesAleatorio]='Y';
								break;
							case 2:
								//RED
								color='R';
								arrayColores[vecesAleatorio]='R';
								break;
							case 3:
								//BLUE
								color='B';
								arrayColores[vecesAleatorio]='B';
								break;
							case 4:
								//PINK
								color='P';
								arrayColores[vecesAleatorio]='P';
								break;	
							case 5:
								//ORANGE
								color='O';
								arrayColores[vecesAleatorio]='O';
								break;
							case 6:
								//VIOLET
								color='V';
								arrayColores[vecesAleatorio]='V';
								break;
							case 7:
								//CYAN
								color='C';
								arrayColores[vecesAleatorio]='C';
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
						SDL_Delay(300);//
						contadorPlayer=0;
					}
				}
				else if(modo_secuencia_colores)
				{
					if(!modo_touch){
						if(contSemaforoSecColores<strlen(arrayColores)){
							if(contSemaforoSecColores==0){//
								color=' ';//SDL_Delay(300);
							}
							if(contSemaforoColorOnOff==0){
								contSemaforoColorOnOff++;//SDL_Delay(150);
							}
							else if(contSemaforoColorOnOff==1){				
								if(firstTimeMSC){//
									SDL_Delay(1500);
									firstTimeMSC=false;
								}
								color=arrayColores[contSemaforoSecColores];
								playSound(color);
								contSemaforoColorOnOff++;
							}
							else if(contSemaforoColorOnOff==2){//
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
						color=' ';//
						SDL_Delay(1000);

						limpiaArrayColores();
						if(!userAnonymous)
						{
							if(puntos>highscore[0])// 
							{
								if(comparaStr(namePlayer[0],username)==0)
								{
									strcpy(namePlayer[2],namePlayer[1]);
									strcpy(namePlayer[1],namePlayer[0]);
									//
									highscore[2]=highscore[1];
									highscore[1]=highscore[0];
									//
									stpcpy(namePlayer[0],username);
									highscore[0]=puntos;
								}
								if(comparaStr(namePlayer[0],username)==1)// 
								{
									stpcpy(namePlayer[0],username);
									highscore[0]=puntos;	
								}
								saveNewHighscore();
							}
							else if(puntos>highscore[1])//  
							{
								if(comparaStr(namePlayer[1],username)==1)
								{
									highscore[2]=highscore[1];
									stpcpy(namePlayer[2],namePlayer[1]);
									stpcpy(namePlayer[1],username);
									highscore[2]=highscore[1];
									highscore[1]=puntos;
								}
								saveNewHighscore();
							}
							else if(puntos>highscore[2])
							{
								if(comparaStr(namePlayer[1],username)==0 || comparaStr(namePlayer[0],username)==0)
								{
									stpcpy(namePlayer[2],username);
									highscore[2]=puntos;
								}
								saveNewHighscore();
							}
						}
					SDL_Delay(2000);//
					fcGameOver();
					}
					contGameOver++;
				}	// 
			}
		}
		else if(modo_highScores)
		{
			if(kUp & KEY_B){// 
				modo_highScores=false;
				modo_menuMain=true;
			}
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
						playSound('A');
				}
			}	
			itoa(highscore[0],chHighscore0,10);
			itoa(highscore[1],chHighscore1,10);
			itoa(highscore[2],chHighscore2,10);
			secuenciaColores();
		}
		else if(modo_blue)
		{
			if(kUp & KEY_B){
				modo_highScores=false;
				modo_menuMain=true;
			}
			// 
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
						contSecuencia=0;semaforo=true;// Para que vuelva a salir el efecto de la secuencia de colores	
						playSound('A');
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
	//
	window = SDL_CreateWindow("Main-Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);	
    	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	
	loadIniVars();
	load_textures(); // 
	load_fonts();// 
	if(leeSaveGame()){
		generaSaveGame();
		leeSaveGame();
	}
	getUserInfo(); // 

	// Main loop
    while(appletMainLoop())
    {	
        //Scan all the inputs. This should be done once for each frame
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
