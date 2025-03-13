#include"Header.h"
#include"LPlayer.h"
#include"Ground.h"


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow("ABC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 500, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //Mix_Music* music = Mix_LoadMUS("meme.mp3");
    //Mix_PlayMusic(music, -1);
    Ground ground("ground.png");
    ground.LoadGround(renderer);
    LPlayer player1(1);
    LPlayer player2(2);
    player1.LoadFile("player1.png", renderer);
    player2.LoadFile("player2.png", renderer);

    bool quit = false;
    SDL_Event e;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            player1.handEvent(e);
            player2.handEvent(e);
        }
        SDL_RenderClear(renderer);
        ground.renderground(renderer, 0);

        player1.updatePlayer(1);
        player1.move(900);
        ground.UpdateP(player1);
        player1.render(renderer, 0);
        player1.UpdateBullets(900, player2, 2);
        player1.renderbullets(renderer);
        ground.UpdateBullets(player1);

        player2.updatePlayer(2);
        player2.move(900);
        ground.UpdateP(player2);
        player2.render(renderer, 0);
        player2.UpdateBullets(900, player1, 1);
        player2.renderbullets(renderer);
        ground.UpdateBullets(player2);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    //Mix_FreeMusic(music);
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    return 0;
}