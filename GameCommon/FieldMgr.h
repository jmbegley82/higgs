#ifndef FIELDMGR_H
#define FIELDMGR_H

#include <stdbool.h>
#include "Sprite.h"

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
bool addRandoToField();  // debugging
bool addSpriteToField(char* identity, char* type, double x, double y);
int getSpriteIndexById(char* identity);
int getSpriteIndexByIdUnsafe(char* identity);
Sprite* getSpriteById(char* identity);
Sprite* getSpriteByIdUnsafe(char* identity);
bool delSpriteById(char* identity);
bool delSpriteByIdUnsafe(char* identity);
bool delSpriteByIndex(int idx);
bool delSpriteByIndexUnsafe(int idx);
bool makeContiguous();
bool makeContiguousUnsafe();

//These two are for using the Unsafe functions externally
//BE CAREFUL!
void lockField();
void unlockField();

#endif //FIELDMGR_H
