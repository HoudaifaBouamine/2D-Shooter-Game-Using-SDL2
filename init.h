#pragma once
#include "struct.h"
#include "defs.h"
#include "Global.h"
#include "draw.h"
#include "logic.h"

void initPlayer();
void initSDL();
void initGame();
void initBullet();




















void initGame() {

	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	initPlayer();
	initBullet();

	stage.bullet_head.next = stage.bullet_tail;
	stage.bullet_tail = NULL;

	app.delegate.logic = game_logic;
	app.delegate.draw = game_draw;

}




































void initPlayer() {

	player.x = PLAYER_POS_X;
	player.y = PLAYER_POS_Y;
	player.dx = PLAYER_SPEED_dX;
	player.dy = PLAYER_SPEED_dY;
	player.health = PLAYER_HEALTH;
	player.texture = loadTexture((char*)"pics/player.png");

	SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);

}

void initBullet() {

	
	player_bullet.dx = PLAYER_BULLET_SPEED_dX;
	player_bullet.dy = PLAYER_BULLET_SPEED_dY;
	player_bullet.health = 1;
	player_bullet.texture = loadTexture((char*)"pics/player_bullet.png");
	player_bullet.next = NULL;

	SDL_QueryTexture(player_bullet.texture, NULL, NULL, &player_bullet.w, &player_bullet.h);

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

