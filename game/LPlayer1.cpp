#include"header.h"
#include"LPlayer1.h"

LPlayer1::LPlayer1() {
	PosX = 0; PosY = 0;
	Vx = 0; Vy = 3;
	JUMP = false;
}
void LPlayer1::handEvent1(SDL_Event e) {
	if (JUMP == false && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP) {
		Vy -= 11 * gravity;
		JUMP = true;
	}
	if (e.type == SDL_KEYDOWN && !e.key.repeat) {
		switch (e.key.keysym.sym) {
			case SDLK_RIGHT: Vx += VEL; break;
			case SDLK_LEFT: Vx -= VEL; break;
		}
		frame++;
		if (frame == 4) frame = 0;
	}else if (e.type == SDL_KEYUP && !e.key.repeat) {
		switch (e.key.keysym.sym) {
			case SDLK_RIGHT: Vx -= VEL; break;
			case SDLK_LEFT: Vx += VEL;  break;
		}
	}
}
void LPlayer1::move1(int SWIDTH) {
	PosX += Vx;
	if (PosX + WIDTH > SWIDTH) PosX = SWIDTH - WIDTH;
	else if (PosX < 0) PosX = 0;
}
void LPlayer1::jump1() {
	if(JUMP == true) {
		Vy += gravity;
		PosY += Vy;
	}
}
void LPlayer1::render1(SDL_Renderer* render, double angle) {
	SDL_Rect RECT = {PosX, PosY, WIDTH, HEIGHT};
	SDL_RenderCopyEx(render, texture, &rectp1[frame], &RECT, angle, NULL, SDL_FLIP_HORIZONTAL);
}
void LPlayer1::LoadFile1(string a, SDL_Renderer* render) {
	SDL_Surface* surface = IMG_Load(a.c_str());
	surface = SDL_ConvertSurface(surface, surface->format, 0);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	texture = SDL_CreateTextureFromSurface(render, surface);
	int w = surface->w, h = surface->h;
	rectp1[0] = { 0, h / 2, w / 4, h / 4 };
	rectp1[1] = { w / 4, h / 2, w / 4, h / 4 };
	rectp1[2] = { w / 2, h / 2, w / 4, h / 4 };
	rectp1[3] = { 3 * w / 4, h / 2, w / 4, h / 4 };
	SDL_FreeSurface(surface);
}