#include"Header.h"
#include"Bullet.h"

Bullet::Bullet(int _x, int _y, bool check) {
	x = _x;
	y = _y;
	right = check;
	Vel = 15;
}