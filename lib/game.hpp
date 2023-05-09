// 游戏内界面，包括游戏场景scene和右侧的计分板等内容
#pragma once
#include <SDL.h>
#include "scene.hpp"
#include "scoreboard.hpp"
#include "enums.hpp"

extern SDL_Renderer* gRenderer;

// namespace cannot control accessibility
class Game {
public:
	Game() {
		pLife = pBomb = 3;
		pGraze = 0;
		pScore = 0;
		keyUp = keyDown = keyLeft = keyRight = false;
		// We treat these status indicating variable as local "global variable"
		scene = new Scene(pLife, pBomb, pGraze, pScore);
		scoreboard = new Scoreboard(pLife, pBomb, pGraze, pScore);
		background.loadFromFile("assets/texture/game/background.png", WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	~Game() {
		if (scene != nullptr) {
			delete scene;
		}
		if (scoreboard != nullptr) {
			delete scoreboard;
		}
	}
	void handleEvent(const SDL_Event& e) {
		// User input handle here, and scene only draws&updates
		// our given status
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				keyUp = true;
				scene->togglePlayerMove(Direction::D_UP, false); 
				break;
			case SDLK_DOWN: 
				keyDown = true;
				scene->togglePlayerMove(Direction::D_DOWN, false); 
				break;
			case SDLK_LEFT: 
				keyLeft = true;
				scene->togglePlayerMove(Direction::D_LEFT, false); 
				break;
			case SDLK_RIGHT: 
				keyRight = true;
				scene->togglePlayerMove(Direction::D_RIGHT, false); 
				break;
			case SDLK_z:
				scene->togglePlayerAttack();
				break;
			case SDLK_LSHIFT:
				scene->togglePlayerSlow();
			}
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_UP: 
				keyUp = false;
				if (!keyUp && !keyDown) {
					scene->togglePlayerMove(Direction::D_UP, true);
				}
				break;
			case SDLK_DOWN: 
				keyDown = false;
				if (!keyUp && !keyDown) {
					scene->togglePlayerMove(Direction::D_DOWN, true);
				}
				break;
			case SDLK_LEFT: 
				keyLeft = false;
				if (!keyLeft && !keyRight) {
					scene->togglePlayerMove(Direction::D_LEFT, true);
				}
				break;
			case SDLK_RIGHT: 
				keyRight = false;
				if (!keyLeft && !keyRight) {
					scene->togglePlayerMove(Direction::D_RIGHT, true);
				}
				break;
			case SDLK_z:
				scene->togglePlayerAttack();
				break;
			case SDLK_LSHIFT:
				scene->togglePlayerSlow();
			}
		}
	};
	void update() {
		if (pLife <= 0) {
			// Do sth about failed
			return;
		};
		scene->update();
		scoreboard->update();
	}
	void render() {
		SDL_RenderSetViewport(gRenderer, NULL);
		background.render(0, 0);
		scene->render();
		scoreboard->render();
	}
private:
	Scene* scene;
	Scoreboard* scoreboard;
	Texture background;
	// in order to prevent unwanted stop
	bool keyUp, keyDown, keyLeft, keyRight;
	int pLife, pBomb, pGraze;
	unsigned long long pScore;
};

