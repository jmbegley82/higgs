#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Sprite.h"
#include "AnimationSet.h"
#include "Debug.h"

char* phasid = "ph animset";

Sprite* getPHSprite(char* identity, double pos_x, double pos_y) {
	printf(DBGFORM"%s, %f, %f\n", DBGSPEC, identity, pos_x, pos_y);
	Sprite* retval = malloc(sizeof(Sprite));
	strcpy(retval->identity, identity);
	retval->anims = getPHAnimSet(phasid, 5);
	retval->pos_x = pos_x;
	retval->pos_y = pos_y;
	return retval;
}

Sprite* newSprite(char* identity, double pos_x, double pos_y) {
	return getPHSprite(identity, pos_x, pos_y);
}

Sprite* cloneSprite(char* identity, Sprite* base) {
	Sprite* retval = malloc(sizeof(Sprite));
	strcpy(retval->identity, identity);
	retval->anims = cloneAnimationSet(base->anims);
	retval->pos_x = base->pos_x;
	retval->pos_y = base->pos_y;
	return retval;
}

QuadPoint getQuad(Sprite* sprite) {
	printf(DBGFORM"\n", DBGSPEC);
	QuadPoint retval; // = {{0,0}, {1,1}, {2,2}, {3,3}};
	double offset_x = 0.f;
	double offset_y = 0.f;
	double width = 0.f;
	double height = 0.f;
	if(sprite) {
		AnimationSet* currentASet = sprite->anims;
		if(currentASet) {
			CelSet* currentCSet = currentASet->sets[currentASet->currentSetIdx];
			if(currentCSet) {
				Cel* currentCel = currentCSet->cels[currentCSet->currentFrame];
				if(currentCel) {
					offset_x = currentCel->offset_x;
					offset_y = currentCel->offset_y;
					width = currentCel->width;
					height = currentCel->height;
				}
			}
		}
	}
	
	retval.topLeft.x = sprite->pos_x + offset_x;
	retval.topLeft.y = sprite->pos_y + offset_y;
	retval.topRight.x = retval.topLeft.x + width;
	retval.topRight.y = retval.topLeft.y;
	retval.bottomLeft.x = retval.topLeft.x;
	retval.bottomLeft.y = retval.topLeft.y + height;
	retval.bottomRight.x = retval.topRight.x;
	retval.bottomRight.y = retval.bottomLeft.y;
	return retval;
}

Point getPosition(Sprite* sprite) {
	printf(DBGFORM"\n", DBGSPEC);
	Point retval = {0.f, 0.f};
	if(sprite) {
		retval.x = sprite->pos_x;
		retval.y = sprite->pos_y;
	}
	return retval;
}

Point setPosition(Sprite* sprite, double x, double y) {
	printf(DBGFORM"%f, %f\n", DBGSPEC, x, y);
	Point retval = {0.f, 0.f};
	if(sprite) {
		// TODO: check bounds and adjust accordingly
		sprite->pos_x = x;
		sprite->pos_y = y;
		retval.x = sprite->pos_x;
		retval.y = sprite->pos_y;
	}
	return retval;
}
