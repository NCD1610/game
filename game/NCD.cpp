#include"Header.h"
#include"LPlayer1.h"
#include"Ground.h"


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow("ABC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 500, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Mix_Music* music = Mix_LoadMUS("meme.mp3");
    Mix_PlayMusic(music, -1);
    Ground ground("ground.png");
    ground.LoadGround(renderer);
    LPlayer1 player1;
    player1.LoadFile1("player1.png", renderer);

    bool quit = false;
    SDL_Event e;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            player1.handEvent1(e);
        }
        SDL_RenderClear(renderer);
        ground.renderground(renderer,0);
        player1.move1(900);
        player1.jump1();
        ground.UpdateP1(player1);
        player1.render1(renderer, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(music);
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    return 0;
}