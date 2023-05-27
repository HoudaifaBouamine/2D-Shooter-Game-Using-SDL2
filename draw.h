#pragma once
#include "Game.h"

void draw(SDL_Texture* texture, int x, int y, int w, int h);
void draw(stEntity entity);

























void game_draw() {

	if(player.health)
		draw(player);
	
	for (stEntity* ptrBullet = stage.bullet_head.next; ptrBullet != NULL; ptrBullet = ptrBullet->next)
	{
		if (ptrBullet->health)
			draw(*ptrBullet);
	}

	for (stEntity* ptrEnemie = stage.enemies_head.next; ptrEnemie != NULL; ptrEnemie = ptrEnemie->next)
	{
		if (ptrEnemie->health)
			draw(*ptrEnemie);
	}
}


























SDL_Texture* loadTexture(char* filename)
{

	SDL_Texture* texture;
	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void draw(SDL_Texture* texture, int x, int y,int w,int h)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void draw(stEntity entity)
{
	SDL_Rect dest;

	dest.x = (int)entity.x;
	dest.y = (int)entity.y;
	dest.w = (int)entity.w;
	dest.h = (int)entity.h;

	SDL_RenderCopy(app.renderer, entity.texture, NULL, &dest);
	
}