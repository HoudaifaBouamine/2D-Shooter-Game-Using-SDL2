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
	//dest.w = w;
	//dest.h = h;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	int fraction = (dest.w / w > dest.h/h)? dest.w / w: dest.h/ h;
	dest.w /= fraction;
	dest.h /= fraction;

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);

	w = dest.w;
	h = dest.h;
}

void draw(stEntity entity)
{
	SDL_Rect dest;

	dest.x = entity.x;
	dest.y = entity.y;
	dest.w = entity.w;
	dest.h = entity.h;

	SDL_RenderCopy(app.renderer, entity.texture, NULL, &dest);
	
}