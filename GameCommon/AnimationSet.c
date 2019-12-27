#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "CelSet.h"
#include "AnimationSet.h"
#include "Debug.h"

char* phcsid = "ph celset";

AnimationSet* getPHAnimSet(char* identity, unsigned int setCount) {
	printf(DBGFORM"%s, %d\n", DBGSPEC, identity, setCount);
	AnimationSet* retval = malloc(sizeof(AnimationSet));
	retval->identity = identity;
	retval->sets = malloc(sizeof(CelSet)*setCount);
	for(int i=0; i<setCount; i++) {
		retval->sets[i] = getPHCelSet(phcsid, 0.5f, 5);
	}
	retval->setCount = setCount;
	retval->currentSetIdx = 0;
	return retval;
}

AnimationSet* newAnimationSet(char* identity) {
	printf(DBGFORM"%s\n", DBGSPEC, identity);
	AnimationSet* retval = malloc(sizeof(AnimationSet));
	//retval->identity = strcpy;
	retval->identity = identity;
	unsigned int setCount = getCSetTypeCount();
	retval->sets = malloc(sizeof(CelSet)*setCount);
	//for(int i=0; i<setCount; i++) {
	//	retval->sets[i] = newCelSet(identity, 0.5f, 5, cels!);
	//}
	Cel** cels = malloc(sizeof(Cel)*5);
	for(int i=0; i<5; i++) {
		cels[i] = newCel(1, 42.f, 42.f, -21.f, -21.f);
	}
	for(int i=0; i<setCount; i++) {
		retval->sets[i] = newCelSet(phcsid, 1.f, 5, cels);
	}
	retval->setCount = setCount;
	retval->currentSetIdx = 0;
	return retval;
}

AnimationSet* cloneAnimationSet(AnimationSet* base) {
	AnimationSet* retval = malloc(sizeof(AnimationSet));
	retval->identity = base->identity;
	retval->sets = base->sets;
	retval->setCount = base->setCount;
	retval->currentSetIdx = base->currentSetIdx;
	return retval;
}

int getCelSetIndex(AnimationSet* aset, char* identity) {
	printf(DBGFORM"%s\n", DBGSPEC, identity);
	int retval = -1;
	for(int i=0; i<aset->setCount && retval == -1; i++) {
		if(strcmp(aset->sets[i]->identity, identity) == 0)
			retval = i;
	}
	return retval;
}

CelSet* getCurrentCelSet(AnimationSet* aset) {
	printf(DBGFORM"\n", DBGSPEC);
	CelSet* retval = NULL;
	if(aset) retval = aset->sets[aset->currentSetIdx];
	return retval;;
}

CelSet* getCelSetById(AnimationSet* aset, char* identity) {
	printf(DBGFORM"%s\n", DBGSPEC, identity);
	CelSet* retval = NULL;
	/*
	for(int i=0; i<aset->setCount && retval != NULL; i++) {
		if(strcmp(aset->sets[i]->identity, identity) == 0)
			retval = aset->sets[i];
	}
	*/
	int idx = getCelSetIndex(aset, identity);
	if(idx >= 0) retval = aset->sets[idx];
	return retval;
}

CelSet* getCelSetByIndex(AnimationSet* aset, unsigned int index) {
	printf(DBGFORM"%d\n", DBGSPEC, index);
	CelSet* retval = NULL;
	if(index < aset->setCount) {
		retval = aset->sets[index];
	}
	return retval;
}

CelSet* setCelSetById(AnimationSet* aset, char* identity) {
	printf(DBGFORM"%s\n", DBGSPEC, identity);
	CelSet* retval = NULL;
	int idx = getCelSetIndex(aset, identity);
	if(idx > -1) {
		retval = setCelSetByIndex(aset, (unsigned int)idx);
	}
	return retval;
}

CelSet* setCelSetByIndex(AnimationSet* aset, unsigned int index) {
	printf(DBGFORM"%d\n", DBGSPEC, index);
	CelSet* retval = NULL;
	retval = getCelSetByIndex(aset, index);
	if(retval) aset->currentSetIdx = index;
	return retval;
}
