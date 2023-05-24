#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include "Game.h"
using namespace std;


void GameLoop() {

    Game* game = nullptr;
    game = new Game;
    float remainder = 0;
    ll then = SDL_GetTicks64();

    while (game->running()) {

        game->do_input();
        game->update();
        game->render();
       // SDL_Delay(16);
        game->GameInfo();
        game->capFrameRate(&then,&remainder);
    }

}

int main(int argc, char* argv[]) {
    
    
    GameLoop();
    return 0;
}
