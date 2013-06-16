#include "stdio.h"
#include <SDL/SDL.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

SDL_Surface* init(int width, int height){

	SDL_Surface *screen;

	// Initialize SDL's video system
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 0;

	}

	screen = SDL_SetVideoMode(width, height, 32, SDL_DOUBLEBUF );
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 0;
	}
	
	return screen;	

}

void cdisplay(SDL_Surface* screen, float* im, int width, int height){

	int x,y;
	int stride = width * height;

	SDL_LockSurface(screen);
	char* raw_pixels = (char*) screen->pixels;
	
	//copy image values to screen
	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {

			int pos = x + y * width;

			int r = MAX(0, MIN(255, im[pos] * 256));
			int g = MAX(0, MIN(255, im[pos + stride] * 256));
			int b = MAX(0, MIN(255, im[pos + 2 * stride] * 256));

			Uint32 pixel_color = SDL_MapRGB(screen->format, r, g, b);
			int offset = (screen->pitch * y + x * screen->format->BytesPerPixel);
			
			memcpy(&raw_pixels[offset], &pixel_color, screen->format->BytesPerPixel);

		}
	}

	SDL_UnlockSurface(screen);

	//refresh screen
	SDL_Flip(screen);

}



