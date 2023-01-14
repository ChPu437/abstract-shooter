#pragma once
#include "character.hpp"
#include "bullet.hpp"

constexpr int BOSS_POS_X = 360;
constexpr int BOSS_POS_Y = 150;

using lBullet = std::list<Bullet*>;

class Enemy : public Character {
public:
	void damage(const int& x) { health -= x; }
	int getHealth() const { return health; }
	virtual void update(const Player*, lBullet&) = 0;
	void destory() {};
protected:
	int health;
};
// boss的更新函数直接写到boss类中，而普通怪的更新采用函数指针方便复用
namespace enemy {
	class Boss : public Enemy {
	public:
		void destory(){}
	};
	namespace boss {
		class Redwarm : public Boss {
		public:
			Redwarm() {
				texture.loadFromFile("assets/texture/character/redwarm.png", 48, 48);
				col = { 24, 24, 22 };
				health = 20;
				posX = BOSS_POS_X;
				posY = BOSS_POS_Y;
				cntX = 0;
				direX = D_NONE;
			}
			void update(const Player* target, lBullet& blt) {
				cntX++;
				switch (direX) {
				case D_LEFT:
					if (cntX <= 100) {
						posX -= 3;
					}
					else {
						direX = D_RIGHT;
						cntX = 0;
					}
					break;
				case D_RIGHT:
					if (cntX <= 100) {
						posX += 3;
					}
					else {
						blt.push_back(new bullet::Flame(posX + 24, posY + 30));
						direX = D_LEFT;
						cntX = 0;
					}
					break;
				case D_NONE:
					if (cntX <= 50) {
						posX -= 3;
					}
					else {
						blt.push_back(new bullet::Flame(posX + 24, posY + 30));
						direX = D_RIGHT;
						cntX = 0;
					}
					break;
				}
				if(cntX % 5 == 0)
					blt.push_back(new bullet::Flame(posX + 24, posY + 30));
			}
		private:
			int cntX;
			Direction direX;
		};
	}
}
