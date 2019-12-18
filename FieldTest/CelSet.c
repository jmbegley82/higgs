//#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Cel.h"
#include "CelSet.h"

CelSet* getPHCelSet(char* identity, double speed, unsigned int frameCount) {
	CelSet* retval = malloc(sizeof(CelSet));
	retval->identity = identity;
	retval->cels = malloc(sizeof(Cel)*frameCount);
	for(int i=0; i<frameCount; i++) {
		retval->cels[i] = getPHCel(i, 20.f, 20.f, -10.f, -10.f);
	}
	retval->speed = speed;
	retval->currentFrame = 0;
	retval->frameCount = frameCount;
	return retval;
}
