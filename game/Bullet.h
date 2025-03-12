#pragma once
#include"Header.h"

struct Bullet {
	SDL_Rect rect;
	int Vel;
	bool right;
	
	Bullet(SDL_Rect, bool check);
};
