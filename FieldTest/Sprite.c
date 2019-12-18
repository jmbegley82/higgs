//#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Sprite.h"
#include "AnimationSet.h"

char* phasid = "ph animset";

Sprite* getPHSprite(char* identity, unsigned int animCount, double pos_x, double pos_y) {
	Sprite* retval = malloc(sizeof(Sprite));
	strcpy(retval->identity, identity);
	retval->anims = malloc(sizeof(AnimationSet)*animCount);
	for(int i=0; i<animCount; i++) {
		retval->anims[i] = getPHAnimSet(phasid, 5);
	}
	retval->pos_x = pos_x;
	retval->pos_y = pos_y;
	return retval;
}
