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

bool UI::Button(float x, float y, float w, float h,
			SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor) {
	SDL_SetRenderDrawColor(SDL_GetRenderer(0), BaseColor.r, BaseColor.g, BaseColor.b, BaseColor.a);
	SDL_FRect buttonRect{x, y, w, h};

	float mouseX, mouseY;
	SDL_MouseButtonFlags buttons =
		SDL_GetMouseState(&mouseX, &mouseY);

	static bool wasPressed = false;
	bool pressed = buttons & SDL_BUTTON_LMASK;
	bool clicked = false;

	if (isHover(buttonRect)) {
		SDL_SetRenderDrawColor(SDL_GetRenderer(0), SelectColor.r, SelectColor.g, SelectColor.b, SelectColor.a);
		if (pressed) {
			SDL_SetRenderDrawColor(SDL_GetRenderer(0), PressColor.r, PressColor.g, PressColor.b, PressColor.a);
			if (!wasPressed)
			{
				clicked = true;
			}
		}
	}
	clicked = false;
	wasPressed = pressed;

	SDL_RenderFillRect(SDL_GetRenderer(0), &buttonRect);
	return clicked;
}