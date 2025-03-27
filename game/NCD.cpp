#include"Header.h"
#include"LPlayer.h"
#include"Ground.h"

int main(int argc, char* argv[]) {
    const char* animation1[8] = { "default1.png", "run1-1.png", "run1-2.png", "run1-3.png", "run1-4.png", "run1-5.png", "run1-6.png", "jump1.png" };
    const char* animation2[8] = { "default2.png", "run2-1.png", "run2-2.png", "run2-3.png", "run2-4.png", "run2-5.png", "run2-6.png", "jump2.png" };

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    srand(time(0));

    SDL_Window* window = SDL_CreateWindow("ABC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 931, 500, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* tex;
    SDL_Rect a{160, 0, 700, 383}, w{415, 410, 70, 70};
    Mix_Music* music = Mix_LoadMUS("music.mp3");
    Mix_PlayMusic(music, -1);
    Mix_Chunk* appear = Mix_LoadWAV("appear.mp3");
    Mix_PlayChannel(-1, appear, 0);
    Ground ground("ground.png");
    ground.LoadGround(renderer);
    LPlayer player1(1, animation1);
    LPlayer player2(2, animation2);
    
    bool quit = false;
    SDL_Event e;
    int res = 0;

    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.x >= 415 && e.button.x <= 485 && e.button.y >= 410 && e.button.y <= 480 && res != 0) {
                res = 0;
                player1.spawnPlayer();
                player2.spawnPlayer();
                ground.clearItem();
            }
            player1.handEvent(e);
            player2.handEvent(e);
        }
        SDL_RenderClear(renderer);
        if (res == 0) {

            ground.UpdateBuff(player1);
            ground.UpdateBuff(player2);
            ground.RandomItem();
            ground.renderground(renderer, 0);

            player1.updatePlayer();
            player1.move(931, 500);
            ground.UpdateP(player1);
            player1.LoadFile(renderer);
            player1.UpdateBullets(931, player2, res);
            ground.UpdateBullets(player1);
            player1.render(renderer);
            player1.renderhp(renderer);
            player1.renderbullets(renderer);

            player2.updatePlayer();
            player2.move(931, 500);
            ground.UpdateP(player2);
            player2.LoadFile(renderer);
            player2.UpdateBullets(931, player1, res);
            ground.UpdateBullets(player2);
            player2.render(renderer);
            player2.renderhp(renderer);
            player2.renderbullets(renderer);
        }else {
            SDL_Surface* surface = IMG_Load("again.png");
            surface = SDL_ConvertSurface(surface, surface->format, 0);
            SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
            tex = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, tex, NULL, &w);
            SDL_DestroyTexture(tex);
            SDL_FreeSurface(surface);
            if (res == 1) {
                SDL_Surface* surface = IMG_Load("p1win.png");
                surface = SDL_ConvertSurface(surface, surface->format, 0);
                SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
                tex = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, tex, NULL, &a);
                SDL_DestroyTexture(tex);
                SDL_FreeSurface(surface);
            }else {
                SDL_Surface* surface = IMG_Load("p2win.png");
                surface = SDL_ConvertSurface(surface, surface->format, 0);
                SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
                tex = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, tex, NULL, &a);
                SDL_DestroyTexture(tex);
                SDL_FreeSurface(surface);
            }
            if (e.key.keysym.sym == SDLK_r) {
                
            }
        }

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