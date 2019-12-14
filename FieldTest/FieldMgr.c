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
CelSet phcs = {NULL, 1.f, 0, 0};

bool getPlaceholderAnim(CelSet* cs) {
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
	if(_field != NULL) {
		purgeField();
		pthread_mutex_lock(&_field_mutex);
			free(_field);
			_field = NULL;
		pthread_mutex_unlock(&_field_mutex);
	}
	pthread_mutex_lock(&_field_mutex);
		_field = malloc(sizeof(Sprite*)*count);
	pthread_mutex_unlock(&_field_mutex);
	if(_field == NULL) return -1;
	pthread_mutex_lock(&_spriteCountMax_mutex);
		_spriteCountMax = count;
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	pthread_mutex_lock(&_spriteCount_mutex);
		_spriteCount = 0;
	pthread_mutex_unlock(&_spriteCount_mutex);
	retval = count;
	printf("initField created _field with %d items\n", count);
	return retval;
}

bool purgeField() {
	pthread_mutex_lock(&_field_mutex);
		for(int i=0; i<_spriteCount; i++) {
			free(_field[i]);
			_field[i] = NULL;
		}
		pthread_mutex_lock(&_spriteCount_mutex);
			_spriteCount = 0;
		pthread_mutex_unlock(&_spriteCount_mutex);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

bool addRandoToField() {
	pthread_mutex_lock(&_spriteCount_mutex);
	pthread_mutex_lock(&_spriteCountMax_mutex);
	if(_spriteCount >= _spriteCountMax) {
		pthread_mutex_unlock(&_spriteCountMax_mutex);
		pthread_mutex_unlock(&_spriteCount_mutex);
		return false;
	}
	pthread_mutex_lock(&_field_mutex);
	Sprite* myNewSprite = malloc(sizeof(Sprite)); //newSprite("poppycock", "animset1", "anim1", 200.f, 200.f);
	newSprite(myNewSprite, "poppycock", "animset1", "anim1", 200.f, 200.f);
	_field[_spriteCount] = myNewSprite;
	printf("myNewSprite's identity is %s\n", myNewSprite->identity);
	pthread_mutex_unlock(&_field_mutex);
	_spriteCount++;
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	pthread_mutex_unlock(&_spriteCount_mutex);
	return true;
}
