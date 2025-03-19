#include"header.h"
#include"Ground.h"
#include"LPlayer.h"
#include"item.h"

Ground::Ground(string file) {
	ground = file;
	rectGround[0] = {160, 420, 610, 80};
	rectGround[1] = {0, 220, 210, 30 };
	rectGround[2] = {250, 315, 150, 20};
	rectGround[3] = {250, 118, 110, 20};
	rectGround[4] = {500, 315, 155, 20 };
	rectGround[5] = {665, 220, 245, 30 };
}
void Ground::renderground(SDL_Renderer* render, double angle) {
		SDL_RenderCopyEx(render, texground, NULL, NULL, angle, NULL, SDL_FLIP_HORIZONTAL);
		/*for (auto it = items.begin(); it != items.end();) {
			if(it->buff == 0) 

		}*/
}
void Ground::LoadGround(SDL_Renderer* render) {
	SDL_Surface* surface = IMG_Load(ground.c_str());
	surface = SDL_ConvertSurface(surface, surface->format, 0);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	texground = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}
void Ground::UpdateP(LPlayer& x) {
	for (int i = 0; i < 6; i++) {
		x.JUMP = true;
		if (x.PosY <= rectGround[i].y + rectGround[i].h && x.PosX + x.WIDTH > rectGround[i].x && x.PosX < rectGround[i].x + rectGround[i].w) {
			if (x.PosY + x.HEIGHT > rectGround[i].y + rectGround[i].h) {
				x.PosY = rectGround[i].y + rectGround[i].h;
				break;
			}else if (x.PosY + x.HEIGHT >= rectGround[i].y) {
				x.PosY = rectGround[i].y - x.HEIGHT;
				if (x.frame == 7) x.frame = 0;
				x.JUMP = false;
				x.Vy = 3;
				break;
			}
		}
	}
}
void Ground::UpdateBullets(LPlayer& x) {
	for (int i = 0; i < 6; i++) {
		for (auto it = x.bullets.begin(); it != x.bullets.end();) {
			if (it->rect.x > rectGround[i].x + rectGround[i].w || it->rect.x + it->rect.w < rectGround[i].x || it->rect.y > rectGround[i].y + rectGround[i].h || it->rect.y + it->rect.h < rectGround[i].y) it++;
			else it = x.bullets.erase(it);
		}
	}
}
void Ground::RandomItem() {
	srand(time(0));
	int y = rand() % 481, x;
	if (y == 105) {
		x = rand() % 111 + 250;
		items.push_back(item{x, y, rand() % 3 });
	}
	if (y == 407) {
		x = rand() % 611 + 160;
		items.push_back(item{ x, y, rand() % 3 });
	}
	if (y == 207) {
		if (rand() % 2 == 0) x = rand() % 211;
		else x = rand() % 246 + 665;
		items.push_back(item{ x, y, rand() % 3 });
	}
	if (y == 302) {
		if (rand() % 2 == 0) x = rand() % 151 + 250;
		else x = rand() % 156 + 500;
		items.push_back(item{ x, y, rand() % 3 });
	}
}