#include"Header.h"
#include"Bullet.h"

Bullet::Bullet(SDL_Rect _rect, bool check) {
	rect = _rect;
	right = check;
	Vel = 15;
}