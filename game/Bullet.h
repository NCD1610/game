#pragma once
#include"Header.h"

struct Bullet {
	int x, y;
	int Vel;
	bool right;
	
	Bullet(int, int, bool check);
};
