#pragma once
#include <SDL3/SDL.h>
class UI
{
public:
	SDL_FPoint mousePos();
	bool Button(float x, float y, float w, float h,
				SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor);
	bool isHover(SDL_FRect rect);
private:
};

