#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {
	int ok = SDL_Init(SDL_INIT_VIDEO);
	if(ok != 0) {
		printf("Could not init SDL!\n");
		return -1;
	}

	SDL_Window* _window = NULL;
	_window = SDL_CreateWindow("GfxTest", 800, 600, 0, 0,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(_window == NULL) {
		printf("Could not create window!\n");
		return -2;
	}

	SDL_Renderer* _renderer = NULL;
	_renderer = SDL_CreateRenderer(_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
			| SDL_RENDERER_TARGETTEXTURE);
	if(_renderer == NULL) {
		printf("Could not create renderer!\n");
		return -3;
	}

	SDL_UpdateWindowSurface(_window);
	while(1) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			// shrug
		}
	}
	return 0;
}
