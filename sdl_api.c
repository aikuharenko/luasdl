#include "stdio.h"
#include <SDL/SDL.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

SDL_Surface* init(int width, int height, const uint8_t * title){

	SDL_Surface *screen;

	// Initialize SDL's video system
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 0;

	}

	screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF );
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 0;
	}
	
	printf("%s\n", title);
	SDL_WM_SetCaption((const char*)title, (const char*)title);
	return screen;	

}

void cdisplay(SDL_Surface* screen, float* im, int width, int height){

	int x, y, i;
	int stride = width * height;

	char* raw_pixels = (char*) screen->pixels;
	
	int *r = (int*) malloc(stride * sizeof(int));
	int *g = (int*) malloc(stride * sizeof(int));
	int *b = (int*) malloc(stride * sizeof(int));
	
	if ((r == NULL) || (g == NULL) || (b == NULL)){
		printf("can't allocate memory\n");
		return;
	}

	for (i = 0; i < stride; i++){
		r[i] = MAX(0, MIN(255, im[i] * 256));
	}

	for (i = 0; i < stride; i++){
		g[i] = MAX(0, MIN(255, im[i + stride] * 256));
	}

	for (i = 0; i < stride; i++){
		b[i] = MAX(0, MIN(255, im[i + 2 * stride] * 256));
	}

	if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

	//copy image values to screen
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {

			int pos = x + y * width;

			Uint32 pixel_color = SDL_MapRGB(screen->format, r[pos], g[pos], b[pos]);
			int offset = (screen->pitch * y + x * screen->format->BytesPerPixel);
			
			memcpy(&raw_pixels[offset], &pixel_color, screen->format->BytesPerPixel);

		}
	}

	if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

	//refresh screen
	SDL_Flip(screen);


	if (r != NULL){
		free(r);
		r = NULL;
	}
	if (g != NULL){
		free(g);
		g = NULL;
	}
	if (b != NULL){
		free(b);
		b = NULL;
	}

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

