#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "fps_lim.hpp"
#include "title.hpp"
#include "game.hpp"

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 960;

bool W_Init();
void W_Quit();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int main(int argc, char* argv[]) {

	if (!W_Init()) {
		std::cerr << "Failed to init SDL2, error: " << SDL_GetError() << std::endl;
		exit(1);
	};
	
	SDL_Event e;
	bool quit = false;
	FpsCapper fpsCapper;
	FpsTimer fpsTimer;

	Game::Init();

	fpsCapper.setTargetFps(60);
	fpsTimer.start();

	while (!quit) {
		fpsCapper.start();
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}

			switch(Game::IsInGame()){
			case true:
				Game::HandleEvent(e);
				break;
			case false:
				quit = true; // for testing
				// Title::HandelEvent(e);
				break;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);

		fpsTimer.render();

		switch (Game::IsInGame()) {
		case true:
			Game::Update();
			Game::Render();
			break;
		case false:
			break;
		}

		SDL_RenderPresent(gRenderer);

		fpsTimer.update();
		fpsCapper.cap();
	}

	Game::Quit();
	W_Quit();

	return 0;
}

bool W_Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) return false;
	if (TTF_Init() < 0) return false;
	if (IMG_Init(IMG_INIT_PNG) < 0) return false;
#ifdef _DEBUG
	gWindow = SDL_CreateWindow("abstract-shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
#else
	gWindow = SDL_CreateWindow("abstract-shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN);
#endif
	if (gWindow == nullptr) return false;
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr) return false;

	return true;
}

void W_Quit() {
	// remember to free audio and texture when used
	SDL_DestroyRenderer(gRenderer), gRenderer = nullptr;
	SDL_DestroyWindow(gWindow), gWindow = nullptr;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
