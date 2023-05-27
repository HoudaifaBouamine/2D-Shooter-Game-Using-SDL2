#pragma once

struct stDelegate {

	void (*logic) (void);
	void (*draw)  (void);

};

struct stApp {

	SDL_Renderer* renderer;
	SDL_Window* window;

	stDelegate delegate;
	char keyboard[MAX_KEYBOARD_KEYS];

};

struct stEntity {

	float x;
	float y;
	int w;
	int h;

	float dx;
	float dy;

	int health;
	int reload;

	SDL_Texture* texture;

	stEntity* next;

};

struct stStage {


	stEntity bullet_head;
	stEntity* bullet_tail;

	stEntity enemies_head;
	stEntity* enemies_tail;
};

