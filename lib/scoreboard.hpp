// 计分板、bomb等显示
#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_FontCache.h>
#include <sstream>

class Scoreboard {
public:
	Scoreboard(const int& _pLife, const int& _pBomb, const int& _pGraze, const unsigned long long& _pScore)
		: pLife(_pLife), pBomb(_pBomb), pGraze(_pGraze), pScore(_pScore) {
		font = FC_CreateFont(); // 大小不一样复用空间不大~~ TODO: font复用~~
		FC_LoadFont(font, gRenderer, "assets/font/jetbrains_mono.ttf", 30, SDL_Color{0, 0, 0, 255}, TTF_STYLE_BOLD);
		if (font == nullptr) throw;
	}
	~Scoreboard() {
		FC_FreeFont(font);
	}
	void update() {
		// if (gPaused) return;
		// to adjust icons if exist
	};
	void render() {
		SDL_RenderSetViewport(gRenderer, &scoreView);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderFillRect(gRenderer, NULL);
		text.str("");
		text << "Score: " << pScore << std::endl;
		text << "Graze: " << pGraze << std::endl;
		text << "Life: " << pLife << std::endl;
		text << "Bomb: " << pBomb << std::endl;
#ifndef _DEBUG
		text << "Alt+F4 to exit." << std::endl;
#endif
		FC_Draw(font, gRenderer, 0, 0, text.str().c_str());
		SDL_RenderSetViewport(gRenderer, NULL);
	};
private:
	FC_Font* font; // can be reused with fpstimer
	std::stringstream text; // can be reused too
	const int& pLife;
	const int& pBomb;
	const int& pGraze;
	const unsigned long long& pScore;
	// const bool& gPaused;
	static const SDL_Rect scoreView;
};

const SDL_Rect Scoreboard::scoreView = {900, 100, 380, 300};

