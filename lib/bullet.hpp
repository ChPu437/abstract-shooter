﻿// 子弹类型的定义
#pragma once
#include <cmath>
#include "texture.hpp"
#include "enums.hpp"
#include "object.hpp"


class Bullet : public Object {
public:
	BulletRelation getBRel() const { return rela; };
	int getDamage() const { return damage; }
	virtual void update(const Object* = nullptr) = 0;
protected:
	BulletType type;
	BulletRelation rela;
	int damage;
};

namespace bullet {
	class Default : public Bullet {
	public:
		Default(const int& damage, const int& _posX, const int& _posY) {
			type = BTYPE_NORMAL, rela = BREL_FRIENDLY;
			posX = _posX, posY = _posY;
			texture.loadFromFile("assets/texture/bullet/default.png", 9, 18);
			spdX = 0, spdY = -10;
			col = { 4, 4, 4 };
			this->damage = damage;
		};
		void update(const Object* target = nullptr) {
			posY += spdY;
		}
	};
	class Flame : public Bullet {
	public:
		Flame(const int& _posX, const int& _posY) {
			type = BTYPE_FLAME, rela = BREL_HOSTILE;
			texture.loadFromFile("assets/texture/bullet/flame.png", 18, 18);
			col = { 9, 13, 4 };
			posX = _posX, posY = _posY;
			slope = 0.0; // 斜率的**倒数**
			flag = true;
		}
		void update(const Object* target) {
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
