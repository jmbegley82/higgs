#ifndef SPRITE_H
#define SPRITE_H

#include "AnimationSet.h"

typedef struct {
	AnimationSet** anims;
	unsigned int currentSetIdx;
	char identity[16];
	double pos_x, pos_y;
} Sprite;

Sprite* getPHSprite(char* identity, unsigned int animCount, double pos_x, double pos_y);

#endif //SPRITE_H
