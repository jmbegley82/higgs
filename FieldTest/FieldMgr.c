#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "FieldMgr.h"

#define SPRITECOUNTMAX_DEFAULT 256

bool		_initialized	= false;
unsigned int	_spriteCount	= 0;
unsigned int	_spriteCountMax	= 0;
Sprite**	_field		= NULL;

pthread_mutex_t _field_mutex;
pthread_mutex_t _initialized_mutex;
pthread_mutex_t _spriteCount_mutex;
pthread_mutex_t _spriteCountMax_mutex;

//Sprite-related:
CelSet phcs = {"default", NULL, 1.f, 0, 0};

bool getPlaceholderAnim(CelSet* cs) {
	cs->identity = phcs.identity;
	cs->cels = phcs.cels;
	cs->speed = phcs.speed;
	cs->currentFrame = phcs.currentFrame;
	cs->frameCount = phcs.frameCount;
	return true;
}

void newSprite(Sprite* sprite, char* identity, char* animSet, char* anim, double x, double y) {
	strcpy(sprite->identity, identity);
	//ignore animSet for now
	//ignore anim for now and use placeholder
	getPlaceholderAnim(&sprite->celset);
	sprite->pos_x = x;
	sprite->pos_y = y;
}

//Field-related:
bool initFieldMgr() {
	if(_initialized) return false;

	pthread_mutex_init(&_field_mutex, NULL);
	pthread_mutex_init(&_initialized_mutex, NULL);
	pthread_mutex_init(&_spriteCount_mutex, NULL);
	pthread_mutex_init(&_spriteCountMax_mutex, NULL);

	pthread_mutex_lock(&_initialized_mutex);
		_initialized = true;
	pthread_mutex_unlock(&_initialized_mutex);

	initField(SPRITECOUNTMAX_DEFAULT);
	return true;
}

int initField(int count) {
	int retval = 0;
	/*
	if(_field != NULL) {
		purgeField();
		pthread_mutex_lock(&_field_mutex);
			free(_field);
			_field = NULL;
		pthread_mutex_unlock(&_field_mutex);
	}
	*/
	pthread_mutex_lock(&_field_mutex);
		if(_field != NULL) {
			purgeFieldUnsafe();
			free(_field);
			_field = NULL;
		}
		_field = malloc(sizeof(Sprite*)*count);
	pthread_mutex_unlock(&_field_mutex);
	if(_field == NULL) return -1;
	setSpriteCountMax(count);
	setSpriteCount(0);
	retval = count;
	printf("initField created _field with %d items\n", count);
	return retval;
}

bool purgeField() {
	pthread_mutex_lock(&_field_mutex);
		if(_field == NULL) {
			pthread_mutex_unlock(&_field_mutex);
			return false;
		}
		purgeFieldUnsafe();
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

bool purgeFieldUnsafe() {
	int sprCount = getSpriteCount();
	for(int i=0; i<sprCount; i++) {
		free(_field[i]);
		_field[i] = NULL;
	}
	setSpriteCount(0);
	return true;
}

int getSpriteCount() {
	int retval = 0;
	pthread_mutex_lock(&_spriteCount_mutex);
		retval = getSpriteCountUnsafe();
	pthread_mutex_unlock(&_spriteCount_mutex);
	return retval;
}

int getSpriteCountMax() {
	int retval = 0;
	pthread_mutex_lock(&_spriteCountMax_mutex);
		retval = getSpriteCountMaxUnsafe();
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	return retval;
}

int setSpriteCount(int count) {
	if(count < 0) return -1;
	int retval = 0;
	pthread_mutex_lock(&_spriteCount_mutex);
		retval = setSpriteCountUnsafe(count);
	pthread_mutex_unlock(&_spriteCount_mutex);
	return retval;
}

int setSpriteCountMax(int count) {
	if(count <= 0) return -1;
	int retval = 0;
	pthread_mutex_lock(&_spriteCountMax_mutex);
		retval = setSpriteCountMaxUnsafe(count);
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	return retval;
}

int getSpriteCountUnsafe() {
	return _spriteCount;
}

int getSpriteCountMaxUnsafe() {
	return _spriteCountMax;
}

int setSpriteCountUnsafe(int count) {
	_spriteCount = count;
	return count;
}

int setSpriteCountMaxUnsafe(int count) {
	_spriteCountMax = count;
	return count;
}

bool addRandoToField() {
	pthread_mutex_lock(&_field_mutex);
		int sprCount = getSpriteCount();
		int sprMax = getSpriteCountMax();
		if(sprCount >= sprMax) {
			pthread_mutex_unlock(&_field_mutex);
			return false;
		}
		Sprite* myNewSprite = malloc(sizeof(Sprite));
		char bsname[16] = "";
		sprintf(bsname, "poppycock%d", rand()%999);
		newSprite(myNewSprite, bsname, "animset1", "anim1", 200.f, 200.f);
		_field[sprCount] = myNewSprite;
		printf("_field[%d].identity is %s\n", sprCount, myNewSprite->identity);
		sprCount++;
		setSpriteCount(sprCount);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

bool addSpriteToField(char* type, char* identity, double x, double y) {
	// dereference type (for now just pass to newSprite)
	// make sure _field is not full
	pthread_mutex_lock(&_field_mutex);
		int sprCount = getSpriteCount();
		if(sprCount >= getSpriteCountMax()) {
			pthread_mutex_unlock(&_field_mutex);
			return false;
		}
		// create Sprite
		Sprite* theNewSprite = malloc(sizeof(Sprite));
		newSprite(theNewSprite, identity, type, "default", x, y);
		// add to _field
		_field[sprCount] = theNewSprite;
		printf("_field[%d].identity is %s; .celset.identity is %s\n", sprCount, _field[sprCount]->identity,
				_field[sprCount]->celset.identity);
		sprCount++;
		setSpriteCount(sprCount);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}
