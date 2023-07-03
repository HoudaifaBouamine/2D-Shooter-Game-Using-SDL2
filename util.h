#pragma once
#include "struct.h"

bool isCollision(stEntity* entity1,stEntity* entity2) {
	
	return (entity1->x < entity2->x + entity2->w && entity1->x + entity1->w > entity2->h && entity1->y < entity2->y + entity2->h && entity1->y + entity1->h > entity2->y);

}


