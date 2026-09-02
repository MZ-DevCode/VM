#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

SDL_FPoint mousePos();

bool isHover(SDL_FRect rect);

bool Button(int id, std::string text, TTF_Font* font, SDL_Color TextColor, SDL_Renderer* renderer,
	float x, float y, float w, float h,
	SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor);

void Text(int id, std::string text, TTF_Font* font, SDL_Renderer* renderer,
		float x = 10, float y = 10,
		SDL_Color TextColor = {255, 255, 255, 255},
		bool haveShadows = true, float shadowPosX = 3, float shadowPosY = 3);