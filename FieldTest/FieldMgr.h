#ifndef FIELDMGR_H
#define FIELDMGR_H

#include <stdbool.h>

typedef unsigned int Image;

typedef struct {
	Image img;			//index# of image to draw
	double width, height;		//self-explanatory
	double offset_x, offset_y;	//distance from center to left/top
} Cel;

typedef struct {
	Cel* cels;			//array of cels
	double speed;			//rate at which cels are flipped
	unsigned int currentFrame;	//current frame
	unsigned int frameCount;	//total number of frames
} CelSet;

typedef struct {
	CelSet celset;
	char identity[16];
	double pos_x, pos_y;
} Sprite;

void newSprite(Sprite* sprite, char* identity, char* animSet, char* anim, double x, double y);

bool initFieldMgr();
int initField(int count);
bool purgeField();
bool addRandoToField();

#endif //FIELDMGR_H
