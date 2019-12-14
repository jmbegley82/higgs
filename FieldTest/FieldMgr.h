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
	char* identity;
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


// FieldMgr-specific
// functions ending in Unsafe will NOT be bothering with mutexes
bool initFieldMgr();
int initField(int count);
bool purgeField();
bool purgeFieldUnsafe();
int getSpriteCount();
int getSpriteCountMax();
int setSpriteCount(int count);
int setSpriteCountMax(int count);
int getSpriteCountUnsafe();
int getSpriteCountMaxUnsafe();
int setSpriteCountUnsafe(int count);
int setSpriteCountMaxUnsafe(int count);
bool addRandoToField();
bool addSpriteToField(char* type, char* identity, double x, double y);
int getSpriteIndexById(char* identity);
int getSpriteIndexByIdUnsafe(char* identity);
Sprite* getSpriteById(char* identity);
Sprite* getSpriteByIdUnsafe(char* identity);

#endif //FIELDMGR_H
