#pragma once
#include"Header.h"
#include"LPlayer1.h"

class Ground {
	private:
		SDL_Rect rectGround[10];
		string ground;
		SDL_Texture* texground;
	public:
		Ground(string);
		void renderground(SDL_Renderer*, double);
		void LoadGround(SDL_Renderer*);
		void UpdateP1(LPlayer1&);
};
