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

char** getCSetTypes();
unsigned int getCSetTypeCount();
unsigned int getCSetTypeIndex(char* type);
char* getCSetTypeString(unsigned int index);
CelSet* getPHCelSet(char* identity, double delay, unsigned int frameCount);
CelSet* newCelSet(char* identity, double delay, unsigned int frameCount, Cel** cels);
CelSet* cloneCelSet(CelSet* base);
bool tickCelSet(CelSet* cs, double time);

//front-end:
//CelSet* netCelSetFromDir(char* path);

#endif //CELSET_H
