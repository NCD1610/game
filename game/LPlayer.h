#pragma once
#include"header.h"
#include"Bullet.h"

class LPlayer{
	friend class Ground;
	private:
		int PosX, PosY;
		int Vx, Vy;
		int hp;
		int VEL;
		int number;
		const char* animation[8];
		SDL_Texture* texture;
		SDL_Texture* texhp;
		int frame = 0;
		bool JUMP, right, buffspeed;
		vector<Bullet> bullets;
		set<int> keysHeld;
		Uint32 lastbullet, lastanimation, lastbuffspeed;
		Mix_Chunk* shoot;
		Mix_Chunk* appear;
	public:
		static const int WIDTH = 32;
		static const int HEIGHT = 32;
		static const int gravity = 3;
		LPlayer(int, const char* []);
		void handEvent(SDL_Event);
		void move(int, int);
		void render(SDL_Renderer*);
		void LoadFile(SDL_Renderer*);
		void UpdateBullets(int, LPlayer&, int&);
		void renderbullets(SDL_Renderer*);
		void renderhp(SDL_Renderer*);
		void updatePlayer();
		void spawnPlayer();
};
