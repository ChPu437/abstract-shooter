#pragma once
#include <cmath>
#include "texture.hpp"
#include "collision.hpp"

class Object {
public:
	Object() {
		spdX = spdY = 0;
		posX = posY = 0;
		col = {0, 0, 0};
	}
	void render() { texture.render(posX, posY); }
	void setPosX(const int& x) { posX = x; }
	void setPosY(const int& x) { posY = x; }
	int getPosX() const { return posX; }
	int getPosY() const { return posY; }
	const Texture& getTexture() const { return texture; }
	int getSpeedX() const { return spdX; }
	int getSpeedY() const { return spdY; }
	void setSpeedX(const int& x) { spdX = x; }
	void setSpeedY(const int& x) { spdY = x; }
	bool calcCollision(const Object& that) const {
		int disSquare = pow((posX + col.x) - (that.getPosX() + that.col.x), 2);
		disSquare += pow((posY + col.y) - (that.getPosY() + that.col.y), 2);
		return disSquare < pow(col.r + that.col.r, 2); 
		// to prevent unset collision wrongly judge as a collision of zero length
	}
public:
	static double ClacDis(const Object* self, const Object* that) {
		return sqrt(pow(self->getPosX() - that->getPosX(), 2) + pow(self->getPosY() - that->getPosY(), 2));
	}
protected:
	Texture texture;
	int posX, posY; // position
	Collision col; // collison
	int spdX, spdY; // speed
};
