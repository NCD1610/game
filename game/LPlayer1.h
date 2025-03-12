#pragma once
#include"header.h"
#include"Bullet.h"

class LPlayer1{
	friend class Ground;
	private:
		int PosX, PosY;
		int Vx, Vy;
		SDL_Texture* texture;
		SDL_Rect rectp1[4];
		int frame = 0;
		bool JUMP, right;
		vector<Bullet> bullets;
		set<int> keysHeld;
	public:
		static const int WIDTH = 32;
		static const int HEIGHT = 32;
		static const int VEL = 7;
		static const int gravity = 3;
		LPlayer1();
		void handEvent1(SDL_Event);
		void move1(int);
		void render1(SDL_Renderer*, double);
		void LoadFile1(string, SDL_Renderer*);
		void UpdateBullets1(int);
		void renderbullets1(SDL_Renderer*);
		void updatePlayer();
};
