#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "def.h"
#include <vector>
using namespace std;

class Game {

    struct stApp {

        SDL_Renderer* renderer;
        SDL_Window* window;

        int up, down, left, right;

        int fire;
    };

    struct stEntity {

        int x;
        int y;
        int dx;
        int dy;
        int w;
        int h;
        int health;

        SDL_Texture* texture;
        
    };

    bool isRunnging = true;

    stApp app = {};

    stEntity player = {};
    stEntity new_fire_ball;
    vector <stEntity> vFire;

public:

    void init() {

        int windowFlags = 0;
        int rendererFlags = SDL_RENDERER_ACCELERATED;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Error init SDL : %s\n", SDL_GetError());
            isRunnging = false;
            return;
        }
        printf("SDL Initilized Successfuly\n");

        app.window = SDL_CreateWindow("2D Shooter Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

        if (!app.window) {

            printf("Error creating %d X %d window : %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            isRunnging = false;
            return;
        }
        printf("Window Created Successfuly\n");

        app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

        if (!app.renderer) {

            printf("Error creating rendrer : %s\n", SDL_GetError());
            isRunnging = false;
            return;
        }

        SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);

        printf("Renderer Created Successfuly\n");

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);


        // Initielizing player character
        _init_player();
        printf("Player Created Successfuly\n");

        // Initilizing fire ball character
        _init_fire_ball();
        printf("Fire ball Created Successfuly\n");

    }

    bool running() { return isRunnging; }

    void do_input() {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            

            switch (event.type)
            {
            case SDL_QUIT: {

                exit(0);
                break;
            }

            case SDL_KEYDOWN: {
                _handle_key_down(&event.key);
                break;
            }

            case SDL_KEYUP: {
                _handle_key_up(&event.key);
                break;
            }
            
            case SDL_MOUSEBUTTONDOWN: {
                _handle_mouse_button_down(&event.button);
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                _handle_mouse_button_up(&event.button);
                break;
            }

            default:
                break;
            }

        }
    }

    void update() {

        // Move Player
        player.x += player.dx*(app.right - app.left);
        player.y += player.dy*(app.down - app.up);

        // Prevent Player from going out of screen
        if (player.x < 0) player.x = 0;
        else if (player.x > SCREEN_WIDTH - player.w) player.x = SCREEN_WIDTH - player.w;

        if (player.y < 0) player.y = 0; 
        else if (player.y > SCREEN_HEIGHT - player.h) player.y = SCREEN_HEIGHT - player.h;












        // Creat Fire
        if (app.fire) {

            new_fire_ball.y = player.y + player.h/2 - new_fire_ball.h/2;
            new_fire_ball.x = player.x + player.w;
            vFire.push_back(new_fire_ball);

            app.fire = 0;
        }

        // Move Fire
        char size = vFire.size();
        for (char i = 0; i < size; i++)
        {
            vFire[i].x += vFire[i].dx;

            if (vFire[i].x > SCREEN_WIDTH) {
                vFire[i].health = 0;
            }
        }


    }

    void render() {

        // Drawing player
        if(player.health)
            _draw(player.texture, player.x, player.y, player.w, player.h);

        for (size_t i = 0; i < vFire.size(); i++)
        {
            if (vFire[i].health) {
                _draw(vFire[i].texture, vFire[i].x, vFire[i].y, vFire[i].w, vFire[i].h);
            }
            else {
                vFire.erase(vFire.begin() + i);
                --i;
            }
        }

        // Apply changes to the screen
        SDL_RenderPresent(app.renderer);

        // Clear Screen From previous drawing
        SDL_RenderClear(app.renderer);

    }

    void clear() {


    }

private:


    SDL_Texture* _loadTexture(char* file_name) {
        return IMG_LoadTexture(app.renderer, file_name);
    }

    void _draw(SDL_Texture* texture, int x, int y,int w,int h) {

        SDL_Rect dest;
        dest.x = x;
        dest.y = y;

        //SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        dest.w = w;
        dest.h = h;

        SDL_RenderCopy(app.renderer, texture, NULL, &dest);
        // SDL_RenderCopy -> par1 = renderer,par2 = texture , par3 Source Rectungle (x,y to start copy and w h to know what size to copy and when we put null on it it means that we need to copy all the texture
        // Par4 -> destenition Rectangle of copy (part of renderer start at x,y on 'dest' and end at x + w and y + h) 
    }

    void _handle_key_down(SDL_KeyboardEvent* key) {

        if (key->repeat != 0) return;

        switch (key->keysym.scancode)
        {
        case SDL_SCANCODE_UP: {
            app.up = 1;
            break;
        }

        case SDL_SCANCODE_DOWN: {
            app.down = 1;
            break;
        }

        case SDL_SCANCODE_LEFT: {
            app.left = 1;
            break;
        }

        case SDL_SCANCODE_RIGHT: {
            app.right = 1;
            break;
        }

        default:
            break;
        }

    }

    void _handle_key_up(SDL_KeyboardEvent* key) {

        if (key->repeat != 0) return;

        switch (key->keysym.scancode)
        {
        case SDL_SCANCODE_UP: {
            app.up = 0;
            break;
        }

        case SDL_SCANCODE_DOWN: {
            app.down = 0;
            break;
        }

        case SDL_SCANCODE_LEFT: {
            app.left = 0;
            break;
        }

        case SDL_SCANCODE_RIGHT: {
            app.right = 0;
            break;
        }

        default:
            break;
        }
    }

    void _handle_mouse_button_down(SDL_MouseButtonEvent* btnMouse) {

        if (btnMouse->button == SDL_BUTTON_LEFT) {

            app.fire = 1;

        }

    }

    void _handle_mouse_button_up(SDL_MouseButtonEvent* btnMouse) {

    }

    void _init_fire_ball() {

        new_fire_ball.x = player.x + player.w;
        new_fire_ball.y = player.y + player.h / 2;
        new_fire_ball.w = 10;
        new_fire_ball.h = 10;
        new_fire_ball.dx = 16;
        new_fire_ball.dy = 0;
        new_fire_ball.health = 1;
        new_fire_ball.texture = _loadTexture((char*)"pics/fireball.png");
    }

    void _init_player() {


        player.x = 50;
        player.y = 100;
        player.w = 80;
        player.h = 81;
        player.dx = 4;
        player.dy = 4;
        player.health = 100;
        player.texture = _loadTexture((char*)"pics/ship.png");

    }

};
