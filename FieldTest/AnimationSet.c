//#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "CelSet.h"
#include "AnimationSet.h"

char* phcsid = "ph celset";

AnimationSet* getPHAnimSet(char* identity, unsigned int setCount) {
	AnimationSet* retval = malloc(sizeof(AnimationSet));
	retval->identity = identity;
	retval->sets = malloc(sizeof(CelSet)*setCount);
	for(int i=0; i<setCount; i++) {
		retval->sets[i] = getPHCelSet(phcsid, 0.5f, 5);
	}
	retval->setCount = setCount;
	return retval;
}
