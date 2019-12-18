#ifndef CELSET_H
#define CELSET_H

#include "Cel.h"

typedef struct {
	char* identity;
	Cel** cels;			//array of cels
	double speed;			//rate at which cels are flipped
	unsigned int currentFrame;	//current frame
	unsigned int frameCount;	//total number of frames
} CelSet;

CelSet* getPHCelSet(char* identity, double speed, unsigned int frameCount);

#endif //CELSET_H
