#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {
	int ok = SDL_Init(SDL_INIT_VIDEO);
	if(ok != 0) {
		printf("Could not init SDL!\n");
		return -1;
	}

	SDL_Window* _window = NULL;
	_window = SDL_CreateWindow("GfxTest", 0, 0, 800, 600,
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

	while(1) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				return 0;
		}
		//SDL_Rect fillRect = { 0, 0, 800, 600 };
		SDL_SetRenderDrawColor(_renderer, 0x1F, 0x00, 0x1F, 0xFF);
		SDL_RenderFillRect(_renderer, NULL); // &fillRect);
		//SDL_UpdateWindowSurface(_window);
		SDL_RenderPresent(_renderer);
		usleep(1000);
	}
	return 0;
}
