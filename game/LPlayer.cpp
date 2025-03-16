#include"header.h"
#include"LPlayer.h"
#include"Bullet.h"

LPlayer::LPlayer(int x, const char* _animation[]) {
	for (int i = 0; i < 8; i++) animation[i] = _animation[i];
	if(x == 2) PosX = 0; PosY = 0;
	if (x == 1) PosX = 931 - WIDTH; PosY = 0;
	Vx = 0; Vy = 3;
	JUMP = true;
	right = true;
	frame = 7;
}

void LPlayer::handEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) keysHeld.insert(e.key.keysym.sym);
	if (e.type == SDL_KEYUP) keysHeld.erase(e.key.keysym.sym);
}

void LPlayer::updatePlayer(int x) {
	Vx = 0; 
	if (x == 1) {
		if (keysHeld.count(SDLK_RIGHT)) {
			Vx += VEL;
			right = true;
		}
		if (keysHeld.count(SDLK_LEFT)) {
			Vx -= VEL;
			right = false;
		}
		if (keysHeld.count(SDLK_UP) && !JUMP) {
			Vy = -10 * gravity;
			JUMP = true;
			frame = 7;
		}
		if (keysHeld.count(SDLK_KP_0) && SDL_GetTicks() - lastbullet >= 500) {
			SDL_Rect b = { PosX, PosY, 5, 5 };
			bullets.push_back(Bullet{ b, right });
			lastbullet = SDL_GetTicks();
		}
	}
	if (x == 2) {
		if (keysHeld.count(SDLK_d)) {
			Vx += VEL;
			right = true;
		}
		if (keysHeld.count(SDLK_a)) {
			Vx -= VEL;
			right = false;
		}
		if (keysHeld.count(SDLK_w) && !JUMP) {
			Vy = -10 * gravity;
			JUMP = true;
			frame = 7;
		}
		if (keysHeld.count(SDLK_SPACE) && SDL_GetTicks() - lastbullet >= 500) {
			SDL_Rect b = { PosX, PosY + 6, 5, 5 };
			bullets.push_back(Bullet{ b, right });
			lastbullet = SDL_GetTicks();
		}
	}
}

void LPlayer::move(int SWIDTH, int SHEIGHT) {
	PosX += Vx;
	if (PosX + WIDTH > SWIDTH) PosX = SWIDTH - WIDTH;
	else if (PosX < 0) PosX = 0;
	if (JUMP == true) {
		if(Vy <= 24) Vy += gravity;
		PosY += Vy;
		if (PosY > SHEIGHT - HEIGHT) PosY = SHEIGHT - HEIGHT;
	}
}

void LPlayer::UpdateBullets(int SWIDTH, LPlayer& other, int x) {
	for (auto it = bullets.begin(); it != bullets.end();) {
		if (it->right == true) it->rect.x += it->Vel;
		else it->rect.x -= it->Vel;
		if (it->rect.x >= SWIDTH) it = bullets.erase(it);
		else if (it->rect.x == 0) it = bullets.erase(it);
		else it++;
	}
	for (auto it = bullets.begin(); it != bullets.end();) {
		if (it->rect.x > other.PosX + other.WIDTH || it->rect.x + it->rect.w < other.PosX || it->rect.y > other.PosY + other.HEIGHT || it->rect.y + it->rect.h < other.PosY) it++;
		else {
			it = bullets.erase(it);
			if (x == 2) other.PosX = 0; other.PosY = 0;
			if (x == 1) other.PosX = SWIDTH - other.WIDTH; other.PosY = 0;
		}
	}
}

void LPlayer::render(SDL_Renderer* render, double angle) {
	SDL_Rect RECT = {PosX, PosY, WIDTH, HEIGHT};
	if(right == false) SDL_RenderCopyEx(render, texture, NULL, &RECT, angle, NULL, SDL_FLIP_HORIZONTAL);
	else SDL_RenderCopyEx(render, texture, NULL, &RECT, angle, NULL, SDL_FLIP_NONE);
}

void LPlayer::renderbullets(SDL_Renderer* render) {
	SDL_SetRenderDrawColor(render, 0, 0, 128, 255);
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		SDL_RenderFillRect(render, &it->rect);
	}
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

void LPlayer::LoadFile(SDL_Renderer* render) {
	if (!JUMP && Vx == 0) frame = 0;
	else if (JUMP) frame = 7;
	else if (SDL_GetTicks() - lastanimation >= 60) {
			frame++;
			if (frame == 7) frame = 1;
			lastanimation = SDL_GetTicks();
	}
	SDL_Surface* surface = IMG_Load(animation[frame]);
	surface = SDL_ConvertSurface(surface, surface->format, 0);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}