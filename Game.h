#pragma once
#include "included_lib.h"

void clear_screen();
void show_game_info();









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

	
	static	FPS fps;

	fps.calc();

}
