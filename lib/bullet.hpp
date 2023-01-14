// 子弹类型的定义
#pragma once
#include <cmath>
#include "texture.hpp"
#include "enums.hpp"
#include "object.hpp"
#include "player.hpp" 


class Bullet : public Object {
public:
	BulletRelation getBRel() const { return rela; };
	int getDamage() const { return damage; }
	virtual void update(const Player* = nullptr) = 0;
protected:
	BulletType type;
	BulletRelation rela;
	int damage;
};

class BulletDefault : public Bullet {
public:
	BulletDefault(const int& damage, const int& pX, const int& pY) {
		type = BTYPE_NORMAL, rela = BREL_FRIENDLY;
		posX = pX, posY = pY;
		texture.loadFromFile("assets/texture/bullet/default.png", 9, 18);
		spdX = 0, spdY = -5;
		col = { 4.5, 4.5, 4.5 };
		this->damage = damage;
	};
	void update(const Player* = nullptr) {
		posY += spdY;
	}
};
namespace bullet {
	class Flame : public Bullet {
	public:
		Flame(const int& pX, const int& pY) {
			type = BTYPE_FLAME, rela = BREL_HOSTILE;
			texture.loadFromFile("assets/texture/bullet/flame.png", 18, 18);
			col = { 9, 13.5, 4.5 };
			posX = pX, posY = pY;
			slope = 0.0; // 斜率的**倒数**
			flag = true;
		}
		void update(const Player* target) {
			if (flag) {
				slope = 1.0 * (posX - target->getPosX()) / (posY - target->getPosY()) + 0.1;
				flag = false;
			}
			posX += 5 * slope;
			posY += 5;
		}
	private:
		double slope;
		bool flag;
	};
}
