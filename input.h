#pragma once

void doInput(void);
void doKeyDown(SDL_KeyboardEvent* event);
void doKeyUp(SDL_KeyboardEvent* event);

// 

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			doKeyDown(&event.key);
			break;

		case SDL_KEYUP:
			doKeyUp(&event.key);
			break;

		default:
			break;
		}
	}
}

void doKeyDown(SDL_KeyboardEvent* event)
{
	if (!event->repeat && event->keysym.scancode < MAX_KEYBOARD_KEYS) {

		app.keyboard[event->keysym.scancode] = 1;
	}
}


void doKeyUp(SDL_KeyboardEvent* event)
{
	
	if (!event->repeat && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app.keyboard[event->keysym.scancode] = 0;
	}

}