#pragma once
#include "struct.h"
#include "defs.h"
#include "Global.h"
#include "draw.h"

void initPlayer();
void initSDL();
void initGame();
void initBullet();




















void initGame() {

	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	initPlayer();
	initBullet();

}




































void initPlayer() {

	player.x = PLAYER_POS_X;
	player.y = PLAYER_POS_Y;
	player.w = PLAYER_WIDTH;
	player.h = PLAYER_HEIGHT;
	player.dx = PLAYER_SPEED_dX;
	player.dy = PLAYER_SPEED_dY;
	player.health = PLAYER_HEALTH;
	player.texture = loadTexture((char*)"pics/player.png");

}

void initBullet() {

	
	bullet.w = PLAYER_BULLET_WIDTH;
	bullet.h = PLAYER_BULLET_HEIGHT;
	bullet.dx = PLAYER_BULLET_SPEED_dX;
	bullet.dy = PLAYER_BULLET_SPEED_dY;
	bullet.health = 0;
	bullet.texture = loadTexture((char*)"pics/player_bullet.png");
}

void initSDL() {

	int rendererFlags = SDL_RENDERER_ACCELERATED, windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

