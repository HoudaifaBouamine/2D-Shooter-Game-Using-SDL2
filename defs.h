#pragma once


// Screen Def
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Input
#define MAX_KEYBOARD_KEYS 350


// Player Def
#define PLAYER_POS_X 100
#define PLAYER_POS_Y 100

#define PLAYER_SPEED_dX 6.0
#define PLAYER_SPEED_dY 6.0
#define PLAYER_HEALTH 100

// Player Bullet Def

#define PLAYER_BULLET_SPEED_dX 16
#define PLAYER_BULLET_SPEED_dY 0
#define PLAYER_BULLET_HEALTH 1


// Enemie Def
#define ENEMIE_POS_X SCREEN_WIDTH
#define ENEMIE_POS_Y rand() % (SCREEN_HEIGHT - 100);
#define ENEMIE_SPEED_dX -(2 + rand() % 5)
#define ENEMIE_SPEED_dY 0.0
#define ENEMIE_HEALTH 200


// Loginc Def
#define ARE_OVERLAPED(x1,y1,w1,h1,x2,y2,w2,h2)((x1 + w1 >= x2)&&(x2+w2 >= x1)&&(y1+h1>=y2)&&(y2+h2 >= y1))
#define SIDE_PLAYER 1
#define SIDE_ENEMY 0
