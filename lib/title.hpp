// TODO: 游戏主界面
#pragma once
#include <SDL.h>
#include "game.hpp"
#include "texture.hpp"
#include "button.hpp"

extern SDL_Renderer* gRenderer;

class Title {
public:
	Title(bool& inGame)
		: inGame(inGame),
		buttonStart("assets/texture/title/buttonStart.png", 300, 200, 400, 100),
		buttonExit("assets/texture/title/buttonExit.png", 300, 300, 400, 100)
	{
		
	}
	~Title(){}
	void handleEvent(const SDL_Event& e) {}
	void update() {
	}
	void render() {
		buttonStart.render();
		buttonExit.render();
	}
	void quit() {
		
	} // 退出过场可以加动画
private:
	bool& inGame;
	Button buttonStart;
	Button buttonExit;
	Texture title;
	Texture background;
};
