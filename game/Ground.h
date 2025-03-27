#pragma once
#include"Header.h"
#include"LPlayer.h"
#include"item.h"

class Ground {
	private:
		SDL_Rect rectGround[8];
		string ground;
		SDL_Texture* texground;
		SDL_Texture* texitem;
		vector<item> items;
		Mix_Chunk* healling;
		Mix_Chunk* upspeed;
	public:
		Ground(string);
		void renderground(SDL_Renderer*, double);
		void LoadGround(SDL_Renderer*);
		void UpdateP(LPlayer&);
		void UpdateBullets(LPlayer&);
		void UpdateBuff(LPlayer&);
		void RandomItem();
		void clearItem();
};
