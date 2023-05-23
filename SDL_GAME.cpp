#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

void GameLoop() {

    Game* game = nullptr;

    game = new Game;
    game->init();
    int cpt = 0;
    while (game->running()) {

        game->do_input();
        game->update();
        game->render();

        SDL_Delay(16);
        // 16ms to get 62 FPS
    }

    game->clear();
    printf("Game End");
}

int main(int argc, char* argv[]) {
    
    
    GameLoop();
    return 0;
}
