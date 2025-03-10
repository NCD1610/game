#pragma once
#include"header.h"

class LPlayer1{
	friend class Ground;
	private:
		int PosX, PosY;
		int Vx, Vy;
		SDL_Texture* texture;
		SDL_Rect rectp1[4];
		int frame = 0;
		bool JUMP;
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
		void jump1();
};
