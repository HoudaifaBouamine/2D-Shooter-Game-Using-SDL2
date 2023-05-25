#pragma once

struct stApp {

	SDL_Renderer* renderer;
	SDL_Window* window;

	char up;
	char down;
	char left;
	char right;
	char fire;

};

struct stEntity {

	short x;
	short y;
	short w;
	short h;

	short dx;
	short dy;

	int health;

	SDL_Texture* texture;
};
