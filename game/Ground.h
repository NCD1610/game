#pragma once
#include"Header.h"
#include"LPlayer.h"

class Ground {
	private:
		SDL_Rect rectGround[8];
		string ground;
		SDL_Texture* texground;
	public:
		Ground(string);
		void renderground(SDL_Renderer*, double);
		void LoadGround(SDL_Renderer*);
		void UpdateP(LPlayer&);
		void UpdateBullets(LPlayer&);
};
