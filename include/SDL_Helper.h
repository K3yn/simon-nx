#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <switch.h>
SDL_Window * 	window;
SDL_Renderer * 	renderer;
SDL_Surface *	surface;
SDL_Texture *	texture;


typedef struct 
{
	SDL_Texture * texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;
} 
images;
images icon, background[1], bgSquare, bgCircle, iconframe,
 colorM3_on[3], colorM3_off[3], colorM4_on[4], colorM4_off[4], colorM5_on[5], colorM5_off[5], colorM8_on[8], colorM8_off[8], 
 numero, numerosColoresTxt, loop, joyconTxt;

static inline SDL_Color SDL_MakeColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color colour = {r, g, b, a};
	return colour;
}

#define WHITE                 SDL_MakeColour(255, 255, 255, 255)
#define RED		              SDL_MakeColour(255, 0, 0, 255)
#define RED_DARK	          SDL_MakeColour(102, 0, 0, 255)
#define GRAY 				  SDL_MakeColour(192, 192, 192, 255)
#define BLACK_BG              SDL_MakeColour(48, 48, 48, 255)
#define BLACK                 SDL_MakeColour(0, 0, 0, 255)
#define STATUS_BAR_LIGHT      SDL_MakeColour(37, 79, 174, 255)
#define STATUS_BAR_DARK       SDL_MakeColour(38, 50, 56, 255)
#define MENU_BAR_LIGHT        SDL_MakeColour(51, 103, 214, 255)
#define MENU_BAR_DARK         SDL_MakeColour(55, 71, 79, 255)
#define SELECTOR_COLOUR_LIGHT SDL_MakeColour(241, 241, 241, 255)
#define SELECTOR_COLOUR_DARK  SDL_MakeColour(76, 76, 76, 255)
#define TITLE_COLOUR          SDL_MakeColour(30, 136, 229, 255)
#define TITLE_COLOUR_DARK     SDL_MakeColour(0, 150, 136, 255)
#define TEXT_MIN_COLOUR_LIGHT SDL_MakeColour(32, 32, 32, 255)
#define TEXT_MIN_COLOUR_DARK  SDL_MakeColour(185, 185, 185, 255)
#define BAR_COLOUR            SDL_MakeColour(200, 200, 200, 255)

void SDL_ClearScreen(SDL_Renderer *renderer, SDL_Color colour);
void SDL_LoadImage(SDL_Texture** texture, u8* buff, size_t size);
void SDL_DrawImageScale(SDL_Texture *texture, int x, int y, int w, int h);
void SDL_DrawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color colour);
void SDL_DrawCircle(SDL_Renderer *renderer, int x, int y, int r, SDL_Color colour);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int Srcx, int Srcy, int Destx, int Desty, int w, int h);
void SDL_DrawText(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char *text);
#endif
