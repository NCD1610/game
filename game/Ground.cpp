#include"header.h"
#include"Ground.h"
#include"LPlayer1.h"

Ground::Ground(string file) {
	ground = file;
	rectGround[0] = {0, 460, 900, 40};
	rectGround[1] = { 0, 380, 100, 40 };
}
void Ground::renderground(SDL_Renderer* render, double angle) {
	for (int i = 0; i < 2; i++) {
		SDL_RenderCopyEx(render, texground, NULL, &rectGround[i], angle, NULL, SDL_FLIP_HORIZONTAL);
	}
}
void Ground::LoadGround(SDL_Renderer* render) {
	SDL_Surface* surface = IMG_Load(ground.c_str());
	surface = SDL_ConvertSurface(surface, surface->format, 0);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	texground = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}
void Ground::UpdateP1(LPlayer1& x) {
	for (int i = 0; i < 2; i++) {
		x.JUMP = true;
		if (x.PosY <= rectGround[i].y + rectGround[i].h && x.PosX + x.WIDTH > rectGround[i].x && x.PosX < rectGround[i].x + rectGround[i].w) {
			if (x.PosY + x.HEIGHT >= rectGround[i].y + rectGround[i].h) {
				x.PosY = rectGround[i].y + rectGround[i].h;
				break;
			}else if (x.PosY + x.HEIGHT >= rectGround[i].y) {
				x.PosY = rectGround[i].y - x.HEIGHT;
				x.JUMP = false;
				x.Vy = 3;
				break;
			}
		}
	}
}
void Ground::UpdateBullets(LPlayer1& x) {
	for (int i = 0; i < 2; i++) {
		for (auto it = x.bullets.begin(); it != x.bullets.end();) {
			if (it->rect.x > rectGround[i].x + rectGround[i].w || it->rect.x + it->rect.w < rectGround[i].x || it->rect.y > rectGround[i].y + rectGround[i].h || it->rect.y + it->rect.h < rectGround[i].y) it++;
			else it = x.bullets.erase(it);
		}
	}
}