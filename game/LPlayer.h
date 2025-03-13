#pragma once
#include"header.h"
#include"Bullet.h"

class LPlayer{
	friend class Ground;
	private:
		int PosX, PosY;
		int Vx, Vy;
		SDL_Texture* texture;
		SDL_Rect rect[4];
		int frame = 0;
		bool JUMP, right;
		vector<Bullet> bullets;
		set<int> keysHeld;
		Uint32 lastbullet;
	public:
		static const int WIDTH = 32;
		static const int HEIGHT = 32;
		static const int VEL = 7;
		static const int gravity = 3;
		LPlayer(int);
		void handEvent(SDL_Event);
		void move(int);
		void render(SDL_Renderer*, double);
		void LoadFile(string, SDL_Renderer*);
		void UpdateBullets(int, LPlayer&, int);
		void renderbullets(SDL_Renderer*);
		void updatePlayer(int);
};
