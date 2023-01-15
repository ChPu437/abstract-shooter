#pragma once
#include "texture.hpp"

using ci = const int;
using cs = const std::string;

class Button {
public:
	Button(cs& texturePath, ci& posX, ci& posY, ci& width, ci& height) {
		texture.loadFromFile(texturePath, width, height);
		selected = false;
		position = { posX, posY, width, height };
	}
	void toggleSelected() {
		selected = !selected;
	}
	void render() {
		if (selected) {
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(gRenderer, &position);
		}
		texture.render(position.x, position.y);
	}
private:
	SDL_Rect position;
	Texture texture;
	bool selected;
};
