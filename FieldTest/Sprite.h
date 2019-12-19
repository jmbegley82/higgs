#ifndef SPRITE_H
#define SPRITE_H

#include "AnimationSet.h"

typedef struct {
	double x, y;
} Point;

typedef struct {
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
} QuadPoint;

typedef struct {
	AnimationSet* anims;
	//unsigned int currentSetIdx;
	char identity[16];
	double pos_x, pos_y;
} Sprite;

Sprite* getPHSprite(char* identity, double pos_x, double pos_y);
QuadPoint getQuad(Sprite* sprite);

#endif //SPRITE_H
