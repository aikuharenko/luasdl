#include "stdio.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

SDL_Surface* init(int width, int height, const uint8_t * title){

	SDL_Surface *screen;

	// Initialize SDL's video system
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 0;

	}

	if (TTF_Init() == -1){
		printf("error initializing ttf\n");
		return 0;
	}

	screen = SDL_SetVideoMode(width, height, 32, SDL_DOUBLEBUF );
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 0;
	}

	SDL_WM_SetCaption((const char*)title, (const char*)title);

	return screen;	

}

void cdisplay(SDL_Surface* screen, float* im, int width, int height){

	int x, y;
	int stride = width * height;

	char* raw_pixels = (char*) screen->pixels;

	if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
	int bpp = screen->format->BytesPerPixel;
	int pitch = screen->pitch;

	//copy image values to screen
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {

			int pos = x + y * width;
			int r = im[pos] * 256;
			if (r < 0) r = 0;
			if (r > 255) r = 255;
				
			int g = im[pos + stride] * 256;
			if (g < 0) g = 0;
			if (g > 255) g = 255;

			int b = im[pos + 2 * stride] * 256;
			if (b < 0) b = 0;
			if (b > 255) b = 255;

			//Uint32 pixel_color = SDL_MapRGB(screen->format, r, g, b);
			Uint32 pixel_color = (r << 16) + (g << 8) + b;
			int offset = (pitch * y + x * bpp);

			memcpy(&raw_pixels[offset], &pixel_color, bpp);

		}
	}

	if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

}

void cdrawtext(SDL_Surface* screen, const uint8_t * fontpath, const uint8_t * text, int fontsize, int x, int y, int r, int g, int b){

	TTF_Font* font = TTF_OpenFont((const char*)fontpath, fontsize);
	if (font == NULL){
		printf("error loading font\n");
		return;
	}

	SDL_Color color = { r, g, b };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, (const char*)text, color);

	if (textSurface == NULL){
		printf("error rendering text\n");
		return;
	}

	SDL_Rect textLocation = { x, y, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);

}

void crefresh(SDL_Surface *screen){

	SDL_Flip(screen);

}



//another way to copy pixels to screen
/*	

	for (i = 0; i < stride; i++){
		pixels[i] = (r[i]<<24) + (g[i]<<16) + (b[i]<<8);
	}

	SDL_Surface *new_screen = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, 
								sizeof(int) * width, 0xFF000000, 0x00FF0000, 0x0000FF00, 0);
	
	if (new_screen == NULL) {
		printf("Unable to creat rgb surface: %s\n", SDL_GetError());
		return;
	}

	SDL_BlitSurface(new_screen, 0, screen, 0);	
*/

