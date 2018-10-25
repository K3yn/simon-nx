#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_Helper.h"
#include "simon_textures.h"

void load_textures(void){
	
	//FONDOS
	
	surface = IMG_Load("romfs:/resources/BG_SQUARE.png");
	bgSquare.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/BG_CIRCLE.png");
	bgCircle.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	// user icon

	surface = IMG_Load("romfs:/resources/icon_frame.png");
	iconframe.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	// Numeros de colores
	surface = IMG_Load("romfs:/resources/NUMBERS_SET.png");
	numerosColoresTxt.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);	
	
	// Joycon
	surface = IMG_Load("romfs:/resources/JOYCON.png");
	joyconTxt.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);	
	
	// Loop
	surface = IMG_Load("romfs:/resources/LOOP.png");
	loop.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);	

	// Colores  M3 ON 

	surface = IMG_Load("romfs:/resources/colors_m3/green-on.png");
	colorM3_on[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m3/red-on.png");
	colorM3_on[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m3/blue-on.png");
	colorM3_on[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Colores M3 OFF

	surface = IMG_Load("romfs:/resources/colors_m3/green-off.png");
	colorM3_off[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m3/red-off.png");
	colorM3_off[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m3/blue-off.png");
	colorM3_off[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	// Colores  M4 ON 

	surface = IMG_Load("romfs:/resources/colors_m4/green-on.png");
	colorM4_on[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m4/red-on.png");
	colorM4_on[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m4/yellow-on.png");
	colorM4_on[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m4/blue-on.png");
	colorM4_on[3].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	// Colores M4 OFF

	surface = IMG_Load("romfs:/resources/colors_m4/green-off.png");
	colorM4_off[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m4/red-off.png");
	colorM4_off[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m4/yellow-off.png");
	colorM4_off[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m4/blue-off.png");
	colorM4_off[3].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);	
	
	// Colores  M5 ON 

	surface = IMG_Load("romfs:/resources/colors_m5/green-on.png");
	colorM5_on[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/red-on.png");
	colorM5_on[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/blue-on.png");
	colorM5_on[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/pink-on.png");
	colorM5_on[3].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/yellow-on.png");
	colorM5_on[4].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	// Colores M5 OFF

	surface = IMG_Load("romfs:/resources/colors_m5/green-off.png");
	colorM5_off[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/red-off.png");
	colorM5_off[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("romfs:/resources/colors_m5/blue-off.png");
	colorM5_off[2].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/pink-off.png");
	colorM5_off[3].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	surface = IMG_Load("romfs:/resources/colors_m5/yellow-off.png");
	colorM5_off[4].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);	
	
}
