#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Cel.h"
#include "CelSet.h"
#include "Debug.h"

char *CSetTypes[] = {"default",
		     "walkl",
		     "walkr",
		     "walkd",
		     "walku",
		     "runl",
		     "runr",
		     "rund",
		     "runu",
		     "attackl",
		     "attackr",
		     "attackd",
		     "attacku",
		     "defendl",
		     "defendr",
		     "defendd",
		     "defendu",
		     "jumpl",
		     "jumpr",
		     "jumpd",
		     "jumpu",
		     "falll",
		     "fallr",
		     "falld",
		     "fallu",
		     "debug"};

char** getCSetTypes() {
	return CSetTypes;
}

unsigned int getCSetTypeCount() {
	return sizeof(CSetTypes)/sizeof(CSetTypes[0]);
}

unsigned int getCSetTypeIndex(char* type) {
	unsigned int retval = 0; // if nothing else we get the default
	bool foundOne = false;
	for(int i=0; i<getCSetTypeCount() && !foundOne; i++) {
		if(strcmp(type,CSetTypes[i])==0) {
			foundOne = true;
			retval = i;
		}
	}
	return retval;
}

char* getCSetTypeString(unsigned int index) {
	char* retval = NULL;
	if(index<getCSetTypeCount())
		retval = CSetTypes[index];
	return retval;
}

CelSet* getPHCelSet(char* identity, double delay, unsigned int frameCount) {
	CelSet* retval = malloc(sizeof(CelSet));
	retval->identity = identity;
	retval->cels = malloc(sizeof(Cel)*frameCount);
	for(int i=0; i<frameCount; i++) {
		retval->cels[i] = newCel(i, 100.f, 100.f, -50.f, -50.f);
	}
	retval->delay = delay;
	retval->timeTilFlip = delay;
	retval->currentFrame = 0;
	retval->frameCount = frameCount;
	return retval;
}

CelSet* newCelSet(char* identity, double delay, unsigned int frameCount, Cel** cels) {
	printf(DBGFORM"%s %f %d\n", DBGSPEC, identity, delay, frameCount);
	CelSet* retval = malloc(sizeof(CelSet));
	retval->identity = identity;
	retval->cels = cels;
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
			if(cs->currentFrame >= cs->frameCount) {
				cs->currentFrame = 0;
			}
			printf(DBGFORM"pop! currentFrame is now %d\n", DBGSPEC, cs->currentFrame);
		}
		return true;
	}
	return false;
}
