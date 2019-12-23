#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include "CelSet.h"

typedef struct {
	char* identity;
	unsigned int setCount;
	unsigned int currentSetIdx;
	CelSet** sets;
} AnimationSet;

AnimationSet* getPHAnimSet(char* identity, unsigned int setCount);
AnimationSet* newAnimationSet(char* identity);

int getCelSetIndex(AnimationSet* aset, char* identity);
CelSet* getCurrentCelSet(AnimationSet* aset);
CelSet* getCelSetById(AnimationSet* aset, char* identity);
CelSet* getCelSetByIndex(AnimationSet* aset, unsigned int index);
CelSet* setCelSetById(AnimationSet* aset, char* identity);
CelSet* setCelSetByIndex(AnimationSet* aset, unsigned int index);

//front-end:
//AnimationSet* netAnimationSetFromDir(char* path);

#endif //ANIMATIONSET_H
