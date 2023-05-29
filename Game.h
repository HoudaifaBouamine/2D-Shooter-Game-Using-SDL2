#pragma once
#include "included_lib.h"

void clear_screen();
void show_game_info();
void cap_fps(int);
void 		capFrameRate();




Benchmark prossesTime;




void game_loop() {

	initSDL();
	initGame();

	while (true) {

		prossesTime.start();

		SDL_RenderClear(app.renderer);

		doInput();

		app.delegate.logic();
		app.delegate.draw();

		SDL_RenderPresent(app.renderer);

		prossesTime.end();

		show_game_info();



		cap_fps(60);
		//capFrameRate();
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
	for (stEntity* ptr = stage.bullet_head.next; ptr != NULL; ptr = ptr->next)
	{
		cpt++;
	}

	printf("Bullets counter : %d    \n", cpt);


	static int counter = 10;
	counter--;

	int fps = prossesTime.FPS;

	if (!counter) {

		printf("FPS : %d              \n", fps);
		printf("PT  : %.2f             \n", float(prossesTime.time) / 1000);
		counter = 10;
	}

}


void cap_fps(int cap = 60) {

	static float then = SDL_GetTicks();

	float def = SDL_GetTicks() - then;

	float wait = (float)1000 / cap - def;
	if (wait < 0)
		wait = 0;
	SDL_Delay(wait);

	then = SDL_GetTicks();

}

static void capFrameRate()
{

	static long then;
	static float remainder = 0;

	long wait, frameTime;

	wait = 16 + remainder;

	remainder -= (int)remainder;

	frameTime = SDL_GetTicks() - then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	remainder += 0.667;

	then = SDL_GetTicks();
}