#pragma once
#include "character.hpp"
#include "bullet.hpp"
#include "hitbox.hpp"

using lBullet = std::list<Bullet*>;

class Player : public Character {
public:
	Player(const PlayerType& type, const int& pX, const int& pY) {
		switch (type) {
		case PTYPE_DEFAULT:
			texture.loadFromFile("assets/texture/character/default.png", 36, 36);
			speed = 5;
			power = 10;
			col	= { 18, 18, 2 };
			cntAttack = -1;
			break;
		}
		isSlow = false;
		posX = pX, posY = pY;
	}
	void toggleSlow() { 
		isSlow = !isSlow;
		speed = speed == 5 ? 3 : 5; 
		if (spdX < 0) spdX = -speed;
		if (spdX > 0) spdX = speed;
		if (spdY < 0) spdY = -speed;
		if (spdY > 0) spdY = speed;
	}
	void toggleAttack() { cntAttack = cntAttack == -1 ? 0 : -1; }
	void toggleMove(const Direction& dire, const bool& moving) {
		switch (dire) {
		case D_UP:
			spdY = moving ? 0 : -speed;
			break;
		case D_DOWN:
			spdY = moving ? 0 : speed;
			break;
		case D_LEFT:
			spdX = moving ? 0 : -speed;
			break;
		case D_RIGHT:
			spdX = moving ? 0 : speed;
			break;
		}
	}
	void update(lBullet& blt) {
		posX += spdX, posY += spdY; 
		if (~cntAttack) {
			cntAttack++;
			if (cntAttack == 5) {
				blt.push_back(new bullet::Default(power / 10, posX + 13, posY - 20));
				cntAttack = 0;
			}
		}
		hitbox.update(isSlow);
	}
	void render() {
		texture.render(posX, posY);
		hitbox.render(posX, posY);
	}
	void destory() {
		// Do this when particle engine is ready
	}
private:
	int speed;
	BulletType bType;
	int power;
	int cntAttack;
	Hitbox hitbox;
	bool isSlow;
};

