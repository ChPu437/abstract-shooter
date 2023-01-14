// 游戏发生的主场景
// TODO: 游戏流程的控制
#pragma once
#include <SDL.h>
#include <list>
#include "object.hpp"
#include "character.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "enums.hpp"

using ull = unsigned long long;

class Scene {
public:
	Scene(int&, int&, int&, ull&);
	~Scene();
	void render();
	void update();
	void addEnemy();
	void togglePlayerMove(const Direction&, const bool&);
	void togglePlayerShoot();
private:
	Direction BorderDetectX(const Object*);
	Direction BorderDetectY(const Object*);
	void BorderDetect(Character*);
	bool BorderDetect(Bullet*);
private:
	std::list<Enemy*>enemy;
	std::list<Bullet*>blt;
	Player* player;
	int& pLife;
	int& pBomb;
	int& pGraze;
	ull& pScore;
	// const bool& gPaused;
	
	static bool isPShooting;
	static int timerPBullet;
	static const SDL_Rect border;
	static const SDL_Rect gameView;
};

bool Scene::isPShooting = false;
int Scene::timerPBullet = 0;
const SDL_Rect Scene::border = { 65, 25, 770, 905 };
const SDL_Rect Scene::gameView = { 66, 26, 768, 903 };

Scene::Scene(int& a, int& b, int& c, ull& d)
	: pLife(a), pBomb(b), pGraze(c), pScore(d) {
	player = new Player(PTYPE_DEFAULT, (gameView.w - 36) / 2, gameView.h - 150);
	timerPBullet = 0;
	isPShooting = false;
	enemy.push_back(new enemy::boss::Redwarm);
}
Scene::~Scene() {
	delete player;
	for (auto i : enemy) {
		delete i;
	}
 	for (auto i : blt) {
		delete i;
	}
}
void Scene::render() {
	// draw frame
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(gRenderer, &border);
	// Set DrawArea to Scene and render
	SDL_RenderSetViewport(gRenderer, &gameView);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, NULL);
	// render player/enemy/bullet
	player->render();
	for (auto i : enemy) {
		i->render();
	}
	for (auto i : blt) {
		i->render();
	}
	SDL_RenderSetViewport(gRenderer, NULL);
}
void Scene::update() {
	// if (gPaused = true) return;

	player->move();
	for (auto i : enemy) {
		i->update(player, blt);
	}
	for (auto i : blt) {
		i->update(player);
	}
	// Shooting, Some use bot animation
	if (isPShooting) {
		timerPBullet++;
		if (timerPBullet == 5) {
			blt.push_back(new BulletDefault(player->getPower() / 10, player->getPosX() + 13, player->getPosY() - 20));
			timerPBullet = 0;
		}
	}
	// Events 
	// // Collision
	for (auto i = blt.begin(); i != blt.end(); ) {
		switch((*i)->getBRel()) {
		case BREL_FRIENDLY:
			if (enemy.empty()) i++;
			for (auto j : enemy) {
				// TODO: Detection for various bullet of various player character	
				if ((*i)->calcCollision(*j)) {
					j->damage((*i)->getDamage());
					delete* i;
					// Do Somthing about health and texture
					i = blt.erase(i);
				}
				else {
					i++;
				}
			}
			break;
		case BREL_HOSTILE:
			if ((*i)->calcCollision(*player)) {
				player->destory();
				pLife--;
				delete* i;
				i = blt.erase(i);
			}
			else {
				i++;
			}
			break;
		}
	}
	// // Enemy Health Check
	for (auto i = enemy.begin(); i != enemy.end(); ) {
		if ((*i)->getHealth() <= 0) {
			delete* i;
			i = enemy.erase(i);
		}
		else {
			i++;
		}
	}
	// Border Detection
	BorderDetect(player);
	for (auto i : enemy) {
		BorderDetect(i);
	}
	for (auto i = blt.begin(); i != blt.end(); ) {
		if (BorderDetect(*i)) {
			delete* i;
			i = blt.erase(i);
		}
		else {
			i++;
		}
	}
}
void Scene::togglePlayerMove(const Direction& dire, const bool& moving) {
	switch (dire) {
	case D_UP:
		if (moving) player->setSpeedY(0);
		else player->setSpeedY(-1 * player->getSpeed());
		break;
	case D_DOWN:
		if (moving) player->setSpeedY(0);
		else player->setSpeedY(player->getSpeed());
		break;
	case D_LEFT: 
		if (moving) player->setSpeedX(0);
		else player->setSpeedX(-1 * player->getSpeed());
		break;
	case D_RIGHT: 
		if (moving) player->setSpeedX(0);
		else player->setSpeedX(player->getSpeed());
		break;
	}
}
void Scene::togglePlayerShoot() {
	switch (isPShooting) {
	case true: isPShooting = false; break;
	case false: isPShooting = true, timerPBullet = 0; break;
	}
}
Direction Scene::BorderDetectX(const Object* obj) {
	if (obj->getPosX() <= 0) {
		return D_LEFT;
	}
	if (obj->getPosX() + obj->getTexture().getWidth() >= border.w) {
		return D_RIGHT;
	}
	return D_NONE;
} 
Direction Scene::BorderDetectY(const Object* obj) {
	if (obj->getPosY() <= 0) {
		return D_UP;
	} // using = and plusing 1 in below to prevent the object mess with border
	if (obj->getPosY() + obj->getTexture().getHeight() >= border.h) {
		return D_DOWN;
	}
	return D_NONE;
} 
void Scene::BorderDetect(Character* ch) {
	switch (BorderDetectX(ch)) {
	case D_LEFT: ch->setPosX(0); break;
	case D_RIGHT: ch->setPosX(gameView.w - ch->getTexture().getWidth()); break;
	}
	switch (BorderDetectY(ch)) {
	case D_UP: ch->setPosY(0); break;
	case D_DOWN: ch->setPosY(gameView.h - ch->getTexture().getHeight()); break;
	}
}
bool Scene::BorderDetect(Bullet* bu) {
	if (bu->getPosX() + bu->getTexture().getWidth() <= 0) return true;
	if (bu->getPosX() >= border.w) return true;
	if (bu->getPosY() >= border.h) return true;
	if (bu->getPosY() + bu->getTexture().getHeight() <= 0) return true;
	return false;
}
