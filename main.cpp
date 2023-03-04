/*
TODO:
游戏流程控制
移动及射击控制->更合理的封装
游戏背景及Scene背景
更合理的FPS计算及控制
主界面、暂停界面、结算界面、失败界面
boss血条
自机/boss出场动画及死亡动画（霸体时间、决死时间、粒子特效）
音效、BGM
最终的二进制打包
存档
*/
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
FC_Font* fontJetbrainsMono;

int main(int argc, char* argv[]) {

	if (!W_Init()) {
		std::cerr << "Failed to init SDL2, error: " << SDL_GetError() << std::endl;
		exit(1);
	};
	
	SDL_Event e;
	bool quit = false;
	FpsCapper fpsCapper;
	FpsTimer fpsTimer;

	Title* title = nullptr;
	Game* game = nullptr;

	fpsCapper.setTargetFps(60);
	fpsTimer.start();

	game = new Game();

	while (!quit) {
		/*if (inGame && game == nullptr) {
			if (title != nullptr) delete title;
			game = new Game(inGame);
		}
		if (!inGame && title == nullptr) {
			if (game != nullptr) delete game;
			title = new Title(inGame);
		}*/
		fpsCapper.start();
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}

			switch(game != nullptr){
			case true:
				game->handleEvent(e);
				break;
			case false:
				title->handleEvent(e);
				break;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);

		fpsTimer.update();

		switch (game != nullptr) {
		case true:
			game->update();
			game->render();
			break;
		case false:
			title->update();
			title->render();
			break;
		}
		fpsTimer.render();

		SDL_RenderPresent(gRenderer);

		fpsCapper.cap();
	}

	if (title != nullptr) delete title;
	if (game != nullptr) delete game;
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
