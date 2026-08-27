#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include "UI.h"

SDL_Window* window;
SDL_Renderer* renderer;

TTF_Font* font;;

UI mainui;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	font = TTF_OpenFont("font/Roboto-Regular.ttf", 20);

	SDL_CreateWindowAndRenderer("VM", 800, 600, SDL_WINDOW_TRANSPARENT, &window, &renderer);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	if(mainui.Button("Start", font, renderer,
		590, 540, 200, 50,
		{ 255, 255, 255, 255 },
		{ 200, 200, 200, 255 },
		{ 150, 150, 150, 255 }
	))
		return SDL_APP_SUCCESS;

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}



void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	
}