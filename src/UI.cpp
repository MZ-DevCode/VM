#include "UI.h"
#include <iostream>

SDL_FPoint mousePos() {
	float x, y;
	SDL_GetMouseState(&x, &y);

	return SDL_FPoint{ x,y };
};

bool isHover(SDL_FRect rect) {
	return mousePos().x >= rect.x &&
		mousePos().x <= rect.x + rect.w &&
		mousePos().y >= rect.y &&
		mousePos().y <= rect.y + rect.h;
}

bool Button(int id, std::string text, TTF_Font* font, SDL_Color TextColor,
	SDL_Renderer* renderer,
	float x, float y, float w, float h,
	SDL_Color BaseColor, SDL_Color SelectColor, SDL_Color PressColor) {

	SDL_SetRenderDrawColor(renderer, BaseColor.r, BaseColor.g, BaseColor.b, BaseColor.a);
	SDL_FRect buttonRect{ x, y, w, h };

	static SDL_Texture* textures[10]{};
	static std::string oldText[10];
	static bool wasPressed[10]{};
	if (id < 0 || id >= 10) return false;
	if (textures[id] == nullptr || oldText[id] != text)
	{
		SDL_Surface* surface =
			TTF_RenderText_Solid(font, text.c_str(), 0, TextColor);

		textures[id] = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_DestroySurface(surface);
		oldText[id] = text;
	}
	SDL_FRect textRect{
		x + (w - textures[id]->w) / 2.0f,
		y + (h - textures[id]->h) / 2.0f,
		(float)textures[id]->w,
		(float)textures[id]->h
	};

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
	SDL_RenderTexture(renderer, textures[id], NULL, &textRect);

	wasPressed[id] = pressed;
	return clicked;
}

void Text(int id, std::string text, TTF_Font* font, SDL_Renderer* renderer, float x, float y, SDL_Color TextColor, bool haveShadows, float shadowPosX, float shadowPosY) {

	static SDL_Texture* textures[10]{};
	static std::string oldText[10];
	if(id < 0 || id >=10) return;


	if (textures[id] == nullptr || oldText[id] != text)
	{
		std::cout
			<< "d | texture: " << textures[id]
			<< " | old: [" << oldText[id] << "]"
			<< " | new: [" << text << "]\n";
		if (textures[id] != nullptr)
			SDL_DestroyTexture(textures[id]);

		SDL_Surface* createText =
			TTF_RenderText_Solid(
				font,
				text.c_str(),
				0,
				TextColor
			);

		textures[id] = SDL_CreateTextureFromSurface(
			renderer,
			createText
		);

		SDL_DestroySurface(createText);

		oldText[id] = text;
	}

	SDL_FRect textRect{
		x,
		y,
		(float)textures[id]->w,
		(float)textures[id]->h
	};

	if (haveShadows) {
		textRect.x += shadowPosX;
		textRect.y += shadowPosY;
		SDL_SetTextureColorMod(textures[id], 0, 0, 0);
		SDL_RenderTexture(renderer, textures[id], NULL, &textRect);
		SDL_SetTextureColorMod(textures[id], TextColor.r, TextColor.g, TextColor.b);
		textRect.x -= shadowPosX;
		textRect.y -= shadowPosY;
	}

	SDL_RenderTexture(renderer, textures[id], NULL, &textRect);
}
