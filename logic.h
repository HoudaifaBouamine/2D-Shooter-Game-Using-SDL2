#pragma once
#include "included_lib.h"

void do_player_bullet(void);
void do_player(void);
void fire_bullet(void);
void do_enemies(void);
void spawn_enemies(void);
void testBulletHitEnemy(stEntity* ptrBullet);












void game_logic(void) {


	do_player();
	do_player_bullet();


	if (--enemySpownTimer <= 0) {

		spawn_enemies();
		enemySpownTimer = 30 + (rand() % 60);
	}

	do_enemies();

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
	stage.bullet_tail->side = SIDE_PLAYER;

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
		
		testBulletHitEnemy(ptrBullet->next);

		if (ptrBullet->next->x > SCREEN_WIDTH || !ptrBullet->next->health) {

			tmp = ptrBullet->next;
			ptrBullet->next = ptrBullet->next->next;
			delete tmp;

		}
		else{
		
			ptrBullet = ptrBullet->next;

		}
	
	}

}

void testBulletHitEnemy(stEntity* ptrBullet) {

	for (stEntity* ptrEnemy = stage.enemies_head.next; ptrEnemy != NULL; ptrEnemy = ptrEnemy->next) {
		if (ptrBullet->side != ptrEnemy->side && ARE_OVERLAPED(ptrBullet->x, ptrBullet->y, ptrBullet->w, ptrBullet->h, ptrEnemy->x, ptrEnemy->y, ptrEnemy->w, ptrEnemy->h))
		{
			ptrBullet->health = 0;
			ptrEnemy->health = 0;
			return;
		}
	}
}

void do_enemies() {

	stEntity* tmp;

	for (stEntity* ptrEnemie = &stage.enemies_head; ptrEnemie->next != NULL; )
	{

		ptrEnemie->next->x += ptrEnemie->next->dx;
		ptrEnemie->next->y += ptrEnemie->next->dy;

		if (ptrEnemie->next->x < 0 - ptrEnemie->next->w || !ptrEnemie->next->health) {

			tmp = ptrEnemie->next;
			ptrEnemie->next = ptrEnemie->next->next;
			delete tmp;
		}
		else {
			ptrEnemie = ptrEnemie->next;
		}

		
	}

}

void spawn_enemies(void) {

	if (stage.enemies_head.next == NULL) {

		stage.enemies_head.next = new stEntity;
		stage.enemies_tail = stage.enemies_head.next;

	}
	else {

		stage.enemies_tail->next = new stEntity;
		stage.enemies_tail = stage.enemies_tail->next;

	}

	*stage.enemies_tail = enemie;

	stage.enemies_tail->x = ENEMIE_POS_X;
	stage.enemies_tail->y = ENEMIE_POS_Y;
	stage.enemies_tail->dx = ENEMIE_SPEED_dX;
}