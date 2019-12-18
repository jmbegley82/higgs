#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Cel.h"
#include "CelSet.h"

CelSet* getPHCelSet(char* identity, double delay, unsigned int frameCount) {
	CelSet* retval = malloc(sizeof(CelSet));
	retval->identity = identity;
	retval->cels = malloc(sizeof(Cel)*frameCount);
	for(int i=0; i<frameCount; i++) {
		retval->cels[i] = getPHCel(i, 20.f, 20.f, -10.f, -10.f);
	}
	retval->delay = delay;
	retval->timeTilFlip = delay;
	retval->currentFrame = 0;
	retval->frameCount = frameCount;
	return retval;
}

bool tickCelSet(CelSet* cs, double time) {
	cs->timeTilFlip -= time;
	if(cs->timeTilFlip <= 0.f) {
		while(cs->timeTilFlip <= 0.f) {
			cs->timeTilFlip += cs->delay;
			cs->currentFrame++;
			printf("tickCelSet:  pop!\n");
			if(cs->currentFrame >= cs->frameCount) {
				cs->currentFrame = 0;
				printf("tickCelSet:  pop POP\n");
			}
		}
		return true;
	}
	return false;
}
