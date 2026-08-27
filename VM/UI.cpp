#include "UI.h"
#include <iostream>

SDL_FPoint UI::mousePos(){
	float x, y;
	SDL_GetMouseState(&x, &y);

	return SDL_FPoint{x,y};
};

bool UI::isHover(SDL_FRect rect) {
	return mousePos().x >= rect.x &&
		mousePos().x <= rect.x + rect.w &&
		mousePos().y >= rect.y &&
		mousePos().y <= rect.y + rect.h;
}

bool UI::Button(std::string text, TTF_Font* font, SDL_Renderer* renderer, float x, float y, float w, float h,
	SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor) {

	SDL_SetRenderDrawColor(renderer, BaseColor.r, BaseColor.g, BaseColor.b, BaseColor.a);
	SDL_FRect buttonRect{x, y, w, h};

	SDL_Surface* createText =
		TTF_RenderText_Solid(font, text.c_str(), 0, { 0, 0, 0, 255 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, createText);
	SDL_FRect textRect{
		x + (w - createText->w) / 2.0f,
		y + (h - createText->h) / 2.0f,
		(float)createText->w,
		(float)createText->h
	};
	SDL_DestroySurface(createText);

	float mouseX, mouseY;
	SDL_MouseButtonFlags buttons =
		SDL_GetMouseState(&mouseX, &mouseY);

	static bool wasPressed = false;
	bool pressed = buttons & SDL_BUTTON_LMASK;
	bool clicked = false;

	if (isHover(buttonRect)) {
		SDL_SetRenderDrawColor(renderer, SelectColor.r, SelectColor.g, SelectColor.b, SelectColor.a);
		if (pressed) {
			SDL_SetRenderDrawColor(renderer, PressColor.r, PressColor.g, PressColor.b, PressColor.a);
			if (!wasPressed)
			{
				clicked = true;
			}
		}
	}
	SDL_RenderFillRect(renderer, &buttonRect);
	SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
	wasPressed = pressed;

	return clicked;
}