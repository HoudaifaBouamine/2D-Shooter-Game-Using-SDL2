#pragma once
#include "included_lib.h"

void do_player_bullet(void);
void do_player(void);
void fire_bullet(void);















void game_logic(void) {


	do_player();
	do_player_bullet();




}













 



void do_player(void) {

	player.dx = (float) PLAYER_SPEED_dX * (app.keyboard[SDL_SCANCODE_RIGHT] - app.keyboard[SDL_SCANCODE_LEFT]);
	player.dy = (float) PLAYER_SPEED_dY * (app.keyboard[SDL_SCANCODE_DOWN] - app.keyboard[SDL_SCANCODE_UP]);

	player.y += player.dy;
	player.x += player.dx;


	if (player.x < 0) player.x = 0;
	else if (player.x + player.w > SCREEN_WIDTH) player.x =  (float)SCREEN_WIDTH - player.w;

	if (player.y < 0) player.y = 0;
	else if (player.y + player.h > SCREEN_HEIGHT) player.y =(float) SCREEN_HEIGHT - player.h;
	
	if (player.reload > 0) player.reload--;

	if (app.keyboard[SDL_SCANCODE_LCTRL] && !player.reload) {

		fire_bullet();
	}
}

void fire_bullet(void) {

	// Called only when player reload == 0

	if (!stage.bullet_head.next) {

		stage.bullet_head.next = new stEntity;
		stage.bullet_tail = stage.bullet_head.next;


	}
	else {

		stage.bullet_tail->next = new stEntity;
		stage.bullet_tail = stage.bullet_tail->next;

	}


	stage.bullet_tail->dx = PLAYER_BULLET_SPEED_dX;
	stage.bullet_tail->dy = PLAYER_BULLET_SPEED_dY;
	stage.bullet_tail->health = 1;
	stage.bullet_tail->texture = player_bullet_textuer;
	stage.bullet_tail->next = NULL;

	SDL_QueryTexture(stage.bullet_tail->texture, NULL, NULL, &stage.bullet_tail->w, &stage.bullet_tail->h);

	stage.bullet_tail->y = player.y + player.h / 2 - stage.bullet_tail->h / 2;
	stage.bullet_tail->x = player.x + player.w;

	player.reload = 8;
}

void do_player_bullet(void) {

	stEntity* tmp;

	for (stEntity* ptrBullet = &stage.bullet_head; ptrBullet->next != NULL;) {


		ptrBullet->next->x += ptrBullet->next->dx;
		//		ptrBullet->y += ptrBullet->dy;

		if (ptrBullet->next->x > SCREEN_WIDTH) {

			tmp = ptrBullet->next;
			ptrBullet->next = ptrBullet->next->next;
			delete tmp;

		}
		else{
		
			ptrBullet = ptrBullet->next;

		}
	
	}

}
