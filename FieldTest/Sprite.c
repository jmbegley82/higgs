//#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Sprite.h"
#include "AnimationSet.h"

char* phasid = "ph animset";

Sprite* getPHSprite(char* identity, double pos_x, double pos_y) {
	Sprite* retval = malloc(sizeof(Sprite));
	strcpy(retval->identity, identity);
	retval->anims = getPHAnimSet(phasid, 5);
	retval->pos_x = pos_x;
	retval->pos_y = pos_y;
	return retval;
}

QuadPoint getQuad(Sprite* sprite) {
	QuadPoint retval; // = {{0,0}, {1,1}, {2,2}, {3,3}};
	AnimationSet* currentASet = sprite->anims;
	CelSet* currentCSet = currentASet->sets[currentASet->currentSetIdx];
	Cel* currentCel = currentCSet->cels[currentCSet->currentFrame];
	retval.topLeft.x = sprite->pos_x + currentCel->offset_x;
	retval.topLeft.y = sprite->pos_y + currentCel->offset_y;
	retval.topRight.x = retval.topLeft.x + currentCel->width;
	retval.topRight.y = retval.topLeft.y;
	retval.bottomLeft.x = retval.topLeft.x;
	retval.bottomLeft.y = retval.topLeft.y + currentCel->height;
	retval.bottomRight.x = retval.topRight.x;
	retval.bottomRight.y = retval.bottomLeft.y;
	return retval;
}
