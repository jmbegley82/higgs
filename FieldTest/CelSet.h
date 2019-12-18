#ifndef CELSET_H
#define CELSET_H

#include <stdbool.h>
#include "Cel.h"

typedef struct {
	char* identity;
	Cel** cels;			//array of cels
	//double speed;			//rate at which cels are flipped
	double delay;			//time between flips
	double timeTilFlip;		//time until next flip
	unsigned int currentFrame;	//current frame
	unsigned int frameCount;	//total number of frames
} CelSet;

CelSet* getPHCelSet(char* identity, double delay, unsigned int frameCount);
bool tickCelSet(CelSet* cs, double time);

#endif //CELSET_H
