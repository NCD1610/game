#include"header.h"
#include"LPlayer1.h"
#include"Bullet.h"

LPlayer1::LPlayer1() {
	PosX = 0; PosY = 0;
	Vx = 0; Vy = 3;
	JUMP = false;
	right = true;
}

void LPlayer1::handEvent1(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) keysHeld.insert(e.key.keysym.sym);
	if (e.type == SDL_KEYUP) keysHeld.erase(e.key.keysym.sym);
}

void LPlayer1::updatePlayer() {
	Vx = 0; 
	if (keysHeld.count(SDLK_RIGHT)) Vx += VEL;  
	if (keysHeld.count(SDLK_LEFT))  Vx -= VEL;  
	if (keysHeld.count(SDLK_UP) && !JUMP) {
		Vy = -11 * gravity;
		JUMP = true;
	}
	if (keysHeld.count(SDLK_KP_0)) bullets.push_back(Bullet{ PosX + 5, PosY, right });
}

void LPlayer1::move1(int SWIDTH) {
	PosX += Vx;
	if (PosX + WIDTH > SWIDTH) PosX = SWIDTH - WIDTH;
	else if (PosX < 0) PosX = 0;
	if (JUMP == true) {
		Vy += gravity;
		PosY += Vy;
	}
}

void LPlayer1::UpdateBullets1(int SWIDTH) {
	for (auto it = bullets.begin(); it != bullets.end();) {
		if (it->right == true) it->x += it->Vel;
		else it->x -= it->Vel;
		if (it->x >= SWIDTH) it = bullets.erase(it);
		else if (it->x == 0) it = bullets.erase(it);
		else it++;
	}
}

void LPlayer1::render1(SDL_Renderer* render, double angle) {
	SDL_Rect RECT = {PosX, PosY, WIDTH, HEIGHT};
	SDL_RenderCopyEx(render, texture, &rectp1[frame], &RECT, angle, NULL, SDL_FLIP_HORIZONTAL);
}

void LPlayer1::renderbullets1(SDL_Renderer* render) {
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		SDL_Rect rect{ it->x, it->y, 5, 5 };
		SDL_RenderFillRect(render, &rect);
	}
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
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