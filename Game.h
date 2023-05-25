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


		app.delegate.logic();
		app.delegate.draw();



		SDL_RenderPresent(app.renderer);

		show_game_info();

		SDL_Delay(16);
	}


}





































void move_player()
{

	player.y += player.dy * (app.keyboard[SDL_SCANCODE_DOWN] - app.keyboard[SDL_SCANCODE_UP]);
	player.x += player.dx * (app.keyboard[SDL_SCANCODE_RIGHT] - app.keyboard[SDL_SCANCODE_LEFT]);

	if (player.y + player.h > SCREEN_HEIGHT) player.y = SCREEN_HEIGHT - player.h;
	else if (player.y < 0) player.y = 0;

	if (player.x + player.w > SCREEN_WIDTH) player.x = SCREEN_WIDTH - player.w;
	else if (player.x < 0) player.x = 0;

}

void move_bullet()
{

	player_bullet.y += player_bullet.dy;
	player_bullet.x += player_bullet.dx;

	
}

void clear_screen()

{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}

void show_game_info()
{

	clear_screen();

	printf("Player Info : \n");
	printf("x  : %f      \n", player.x);
	printf("y  : %f      \n", player.y);
	printf("w  : %d      \n", player.w);
	printf("h  : %d      \n", player.h);
	printf("dx : %f      \n", player.dx);
	printf("dy : %f      \n", player.dy);

	printf("\n\n");
	int cpt = 0;
	for (stEntity* ptr = stage.bullet_head.next; ptr != NULL ; ptr = ptr->next)
	{
		cpt++;
	}

	printf("Bullets counter : %d    \n", cpt);
}
