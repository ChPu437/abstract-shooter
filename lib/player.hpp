#pragma once
#include "character.hpp"

class Player : public Character {
public:
	Player(const PlayerType& type, const int& pX, const int& pY) {
		switch (type) {
		case PTYPE_DEFAULT:
			texture.loadFromFile("assets/texture/character/default.png", 36, 36);
			speed = 5;
			power = 10;
			col	= { 18, 18, 2 };
			break;
		}
		posX = pX, posY = pY;
	}
	int getSpeed() const { return speed; }
	int getPower() const { return power; }
	BulletType getBulletType() const { return bType; }
	void move() { posX += spdX, posY += spdY; }
	void destory() {
		// Do this when particle engine is ready
	}
private:
	int speed;
	BulletType bType;
	int power;
};
