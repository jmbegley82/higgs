#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include "CelSet.h"

typedef struct {
	char* identity;
	unsigned int setCount;
	CelSet** sets;
} AnimationSet;

AnimationSet* getPHAnimSet(char* identity, unsigned int setCount);

#endif //ANIMATIONSET_H
