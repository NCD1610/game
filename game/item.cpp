#include"Header.h"
#include"item.h"
#include"LPlayer.h"

item::item(int x, int y, int k) {
	rect = { x, y, 30, 30 };
	buff = k;
}	