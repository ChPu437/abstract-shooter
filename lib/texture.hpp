// 对SDL_Texture的封装，使移动、渲染等更易使用
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

typedef unsigned int uint;

extern SDL_Renderer* gRenderer;

class Texture {
public:
	Texture(const int& = 0, const int& = 0);
	virtual ~Texture();
	void free();
	bool loadFromFile(const std::string&, const int& = 0, const int& = 0);
	void render(const int&, const int&, const SDL_Rect* = nullptr, const double& = 0.0, const SDL_Point* = nullptr, const SDL_RendererFlip& = SDL_FLIP_NONE);
	void setAlpha(const Uint8& alpha) {
		SDL_SetTextureAlphaMod(texture, alpha);
	}
	int getWidth() const;
	int getHeight() const;
protected:
	SDL_Texture* texture;
	int width, height;
};

Texture::Texture(const int& w, const int& h) {
	texture = nullptr;
	width = w, height = h;
}
Texture::~Texture() {
	free();
}
void Texture::free() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = height = 0;
	}
}
bool Texture::loadFromFile(const std::string& path, const int& w, const int& h) {
	free(); // free existing texture
	if (w) width = w;
	if (h) height = h;
	SDL_Surface* surf = nullptr;
	surf = IMG_Load(path.c_str());
	if (surf == nullptr) return false;
	texture = SDL_CreateTextureFromSurface(gRenderer, surf);
	SDL_FreeSurface(surf); // prevent oom
	return texture != nullptr;
}
void Texture::render(const int& x, const int& y, const SDL_Rect* clip, const double& angle, const SDL_Point* center, const SDL_RendererFlip& flip){
	SDL_Rect renderQuad = {x, y, width, height}; // set render space
	if (clip != nullptr) { // set clip if exists
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, angle, center, flip);
}
int Texture::getWidth() const {
	return width;
}
int Texture::getHeight() const {
	return height;
}
