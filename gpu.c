#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "gpu.h"

#define WINDOW_HEIGHT 144
#define WINDOW_WIDTH 160

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
unsigned char *wholeMemory;

unsigned char * getTile(unsigned short startAddress, unsigned char offset){
	offset *= 16;	// There are 16 bytes per tile
	unsigned short address = startAddress;
	if(startAddress == 0x9000) address += (signed char) offset;
	else address += offset;

	unsigned char *tile = malloc(sizeof(unsigned char) * 8 * 8);
	unsigned char a, b;	// The two bytes of memory we are using.
	int x, y;
	for(y = 0; y < 8; y ++){
		a = wholeMemory[address + (y * 2)];
		b = wholeMemory[address + (y * 2) + 1];
		for(x = 0; x < 8; x ++){
			tile[y * 8 + x] = ((a | b) & (1 << x)) >> x;
		}
	}
	return tile;
}

void createDisplay(unsigned char *memory){
	wholeMemory = memory;
	if(window == NULL || renderer == NULL){
                SDL_Init(SDL_INIT_EVERYTHING);
                SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
                if (renderer == NULL){
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 1;
                }
        }
}

void destroyDisplay(){
        SDL_DestroyWindow(window);
        SDL_Quit();
}

unsigned char getTileColor(unsigned char val){
	if(val == 0) return 0;
	if(val == 1) return 64;
	if(val == 2) return 128;
	if(val == 3) return 255;
}

void drawTile(unsigned char *tile, int startX, int startY){
	int x, y, color;
	for(x = 0; x < 8; x ++){
		for(y = 0; y < 8; y ++){
			color = getTileColor(tile[y * 8 + x]);
			SDL_SetRenderDrawColor(renderer, 0, color, color, color);
			SDL_RenderDrawPoint(renderer, x + startX, y + startY);
		}
	}
}

void display(){
	if(window == NULL || renderer == NULL) return;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	int x, y;
	int tileID = 0;
	for(x = 0; x < WINDOW_WIDTH; x += 8){
		for(y = 0; y < WINDOW_HEIGHT; y += 8){
			drawTile(getTile(0x8000, tileID), x, y);
			tileID ++;
		}
	}

	SDL_RenderPresent(renderer);
}
