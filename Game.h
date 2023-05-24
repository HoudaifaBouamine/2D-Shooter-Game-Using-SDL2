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

    struct stHealthBar {

        SDL_Texture* out = NULL;
        SDL_Texture* in = NULL;

    };

    struct stEntity {

        int x;
        int y;
        int dx;
        int dy;
        int w;
        int h;
        float health;// if health = 0 delete entity
        int reload;


        SDL_Texture* texture;
        stHealthBar health_bar;

    };

 

    bool isRunnging = true;

    stApp app = {};

    stEntity player = {};
    stEntity pacman = {};
    stEntity new_fire_ball;
    vector <stEntity> vFire;

public:

    void init_SDL() {

        int windowFlags = 0;
        int rendererFlags = SDL_RENDERER_ACCELERATED;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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

        printf("Image Init Successfuly\n");


    }

    bool running() { return isRunnging; }

    void do_input() {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            

            switch (event.type)
            {
            case SDL_QUIT: {

                clear(); 
                printf("Game End");
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

        // Update Player Reload
        if (player.reload > 0) player.reload--;




        //\\----------------------------------------------------------------//\\




        // Creat Fire
        if (app.fire && !player.reload) {

            new_fire_ball.y = player.y + player.h/2 - new_fire_ball.h/2;
            new_fire_ball.x = player.x + player.w;
            vFire.push_back(new_fire_ball);
            player.reload = PLAYER_RELOAD_TIME;
        }

        // Move Fire
       


       

//        Update Enemie


        static float counter = 0;
        counter+= 0.01;

        pacman.y = PACMAN_Y_POS + PACMAN_Y_SPEED * sin(counter);
        

        // hit enemy

        char size = vFire.size();
        for (char i = 0; i < size; i++)
        {
            vFire[i].x += vFire[i].dx;

            if (vFire[i].x > SCREEN_WIDTH) {
                vFire[i].health = 0;
            }

            if (pacman.health > 0) {
                // if (vFire[i].x + vFire[i].w >= pacman.x && vFire[i].x <= pacman.x + pacman.w && !(vFire[i].y <= pacman.y + pacman.h && vFire[i].y + vFire[i].h <= pacman.y))
                if (vFire[i].y >= pacman.y && vFire[i].y <= pacman.y + pacman.h && vFire[i].x + vFire[i].w >= pacman.x + pacman.w / 2 && vFire[i].x <= pacman.x + pacman.w)
                {
                    if (pacman.health > 0) {
                        vFire[i].health = 0;
                        pacman.health -= 100;
                    }
                }
            }
        }

    }


    void render() {

        // Show player health
        _draw(player.health_bar.in, 52, 27, 163 * (player.health / PLAYER_MAX_HEALTH), 20);
        _draw(player.health_bar.out, 20, 20, 200, 35);

        
        // Drawing player
        if (player.health > 0) {
            _draw(player.texture, player.x, player.y, player.w, player.h);
        }

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

        // Drawing pacman

        if (pacman.health > 0) {
            _draw(pacman.texture, pacman.x, pacman.y, pacman.w, pacman.h);

            _draw(pacman.health_bar.in, pacman.x + 16, pacman.y - 15, 165 * 0.5 * (pacman.health / PACMAN_MAX_HEALTH), 10);// pacman.x, pacman.y - 20, pacman.w, 20);
            _draw(pacman.health_bar.out, pacman.x,pacman.y - 18, 200 * 0.5, 17);// pacman.x, pacman.y - 20, pacman.w, 20);

        }


        // Apply changes to the screen
        SDL_RenderPresent(app.renderer);

        // Clear Screen From previous drawing
        SDL_RenderClear(app.renderer);

    }

    void clear() {


    }

    static void capFrameRate(ll* then, float* remainder)
    {
        long wait, frameTime;

        wait = 16 + *remainder;

        *remainder -= (int)*remainder;

        frameTime = SDL_GetTicks() - *then;

        wait -= frameTime;

        if (wait < 1)
        {
            wait = 1;
        }

        SDL_Delay(wait);

        *remainder += 0.667;

        *then = SDL_GetTicks();
    }

    ll start_time;

    void GameInfo() {

        static int cpt = 5;
        if (!cpt--) {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,10 });
            printf("FPS : %d  \n", 1000 / (SDL_GetTicks64() - start_time));
            printf("Player HP : %d  \n", player.health);
            printf("Pacman HP : %d  \n", pacman.health);

            cpt = 5;
        }

        start_time = SDL_GetTicks64();
    }

    Game() {
        start_time = SDL_GetTicks64();
        init_SDL();
        _init_game();
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

        if (btnMouse->button == SDL_BUTTON_LEFT) {

            app.fire = 0;

        }
    }

    void _init_fire_ball() {

        new_fire_ball.x = player.x + player.w;
        new_fire_ball.y = player.y + player.h / 2;
        new_fire_ball.w = 30;
        new_fire_ball.h = 10;
        new_fire_ball.dx = 16;
        new_fire_ball.dy = 0;
        new_fire_ball.health = 1;
        new_fire_ball.texture = _loadTexture((char*)"pics/pacman.png");
    }

    void _init_player() {


        player.x = 50;
        player.y = 100;
        player.w = 80;
        player.h = 81;
        player.dx = 5;
        player.dy = 5;
        player.health = PLAYER_MAX_HEALTH;
        player.reload = 0;
        player.texture = _loadTexture((char*)"pics/ship.png");
        player.health_bar.out = _loadTexture(((char*)"pics/emptyhealthbar.png"));
        player.health_bar.in = _loadTexture(((char*)"pics/healthbar.png"));

    }

    void _init_pacman() {


        pacman.x = 1000;
        pacman.y = PACMAN_Y_POS;
        pacman.w = 120;
        pacman.h = 121;
        pacman.dx = 0;
        pacman.dy = PACMAN_Y_SPEED;
        pacman.health = PACMAN_MAX_HEALTH;
        pacman.reload = 0;
        pacman.texture = _loadTexture((char*)"pics/pacman.png");
        pacman.health_bar.out = _loadTexture(((char*)"pics/emptyhealthbar.png"));
        pacman.health_bar.in = _loadTexture(((char*)"pics/healthbar.png"));

    }

    void _init_game() {

        // Initielizing player character
        _init_player();
        printf("Player Created Successfuly\n");

        // Initilizing fire ball character
        _init_fire_ball();
        printf("Fire ball Created Successfuly\n");

        _init_pacman();
        printf("pacman Created Successfuly\n");


        

    }
};
