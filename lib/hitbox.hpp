#pragma once
#include "object.hpp"

class Hitbox {
public:
	Hitbox() {
		texture.loadFromFile("assets/texture/character/hitbox.png", 96, 96);
		angle = alpha = 0;
		col = { 48, 48, 20 };
	}
	void render(const int& _posX, const int& _posY) {
		if (!alpha) return;
		texture.render(_posX - 30, _posY - 30, NULL, angle, &col.center);
	}
	void update(const bool& show) {
		alpha += show ? +20 : -20;
		alpha = alpha > 255 ? 255 : alpha;
		alpha = alpha < 0 ? 0 : alpha;
		angle = angle == 359 ? 0 : angle + 1;
		texture.setAlpha(alpha);
	}
private:
	int alpha;
	int angle; 
	Texture texture;
	Collision col;
};

