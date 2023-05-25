#pragma once
#include "included_lib.h"

void move_player();
void clear_screen();
void show_game_info();
void move_bullet();










void game_loop() {

	initSDL();
	initGame();


	while (true) {

		SDL_RenderClear(app.renderer);

		doInput();

		move_player();

		if (bullet.health)
		{
			bullet.x += bullet.dx;
			bullet.y += bullet.dy;

			if (bullet.x > SCREEN_WIDTH) {
				bullet.health = 0;
			}
		}
		if (app.fire && !bullet.health) {

			bullet.health = 1;
			bullet.x = player.x + player.w;
			bullet.y = player.y + player.h / 2 - bullet.h / 2;
		}


		move_bullet();

		if (player.health) draw(player);

		if (bullet.health) draw(bullet);

		SDL_RenderPresent(app.renderer);

		show_game_info();

		SDL_Delay(16);
	}


}





































void move_player()
{

	player.y += player.dy * (app.down - app.up);
	player.x += player.dx * (app.right - app.left);

	if (player.y + player.h > SCREEN_HEIGHT) player.y = SCREEN_HEIGHT - player.h;
	else if (player.y < 0) player.y = 0;

	if (player.x + player.w > SCREEN_WIDTH) player.x = SCREEN_WIDTH - player.w;
	else if (player.x < 0) player.x = 0;

}

void move_bullet()
{

	bullet.y += bullet.dy;
	bullet.x += bullet.dx;

	
}

void clear_screen()

{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}

void show_game_info()
{

	clear_screen();

	printf("Player Info : \n");
	printf("x  : %d      \n", player.x);
	printf("y  : %d      \n", player.y);
	printf("w  : %d      \n", player.w);
	printf("h  : %d      \n", player.h);
	printf("dx : %d      \n", player.dx);
	printf("dy : %d      \n", player.dy);

	printf("\n\n");
}
