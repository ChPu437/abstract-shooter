#pragma once
#include <SDL.h>

struct Collision {
	SDL_Point center;
	int r; 
	// center and radius, as relative to object position
};

