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
	static void HandleEvent(const SDL_Event&);
	static void Init();
	static void Update();
	static void Render();
	static void Quit();
	static bool IsInGame();
private:
	static bool inGame;
	static Scene* scene;
	static Scoreboard* scoreboard;
	// in order to prevent unwanted stop
	static bool keyUp, keyDown, keyLeft, keyRight;
	static int pLife, pBomb, pGraze;
	static unsigned long long pScore;
};

bool Game::inGame;
int Game::pLife, Game::pBomb, Game::pGraze;
unsigned long long Game::pScore = 0;
bool Game::keyUp = false;
bool Game::keyDown = false;
bool Game::keyLeft = false;
bool Game::keyRight = false;
Scene* Game::scene = nullptr;
Scoreboard* Game::scoreboard = nullptr;

void Game::Init() {
	inGame = true;
	pLife = pBomb = 3;
	pGraze = pScore = 0;
	scene = new Scene(pLife, pBomb, pGraze, pScore);
	scoreboard = new Scoreboard(pLife, pBomb, pGraze, pScore);
}
void Game::Quit() {
	if (scene != nullptr) {
		delete scene;
	}
	if (scoreboard != nullptr) {
		delete scoreboard;
	}
}
void Game::HandleEvent(const SDL_Event& e) {
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
			scene->togglePlayerShoot();
			break;
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
			scene->togglePlayerShoot();
			break;
		}
	}
}
void Game::Update() {
	if (pLife <= 0) {
		inGame = false;
	};
	scene->update();
	scoreboard->update();
}
void Game::Render() {
	scene->render();
	scoreboard->render();
}
bool Game::IsInGame() {
	return inGame;
}
