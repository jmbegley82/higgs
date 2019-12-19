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
	retval->currentSetIdx = 0;
	return retval;
}

int getCelSetIndex(AnimationSet* aset, char* identity) {
	int retval = -1;
	for(int i=0; i<aset->setCount && retval == -1; i++) {
		if(strcmp(aset->sets[i]->identity, identity) == 0)
			retval = i;
	}
	return retval;
}

CelSet* getCurrentCelSet(AnimationSet* aset) {
	CelSet* retval = NULL;
	if(aset) retval = aset->sets[aset->currentSetIdx];
	return retval;;
}

CelSet* getCelSetById(AnimationSet* aset, char* identity) {
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
	CelSet* retval = NULL;
	if(index < aset->setCount) {
		retval = aset->sets[index];
	}
	return retval;
}

CelSet* setCelSetById(AnimationSet* aset, char* identity) {
	CelSet* retval = NULL;

	return retval;
}

CelSet* setCelSetByIndex(AnimationSet* aset, unsigned int index) {
	CelSet* retval = NULL;
	return retval;
}
