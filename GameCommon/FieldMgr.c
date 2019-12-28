#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "FieldMgr.h"
#include "Sprite.h"
#include "Debug.h"

#define SPRITECOUNTMAX_DEFAULT 256

bool		_initialized	= false;
unsigned int	_spriteCount	= 0;
unsigned int	_spriteCountMax	= 0;
Sprite**	_field		= NULL;

pthread_mutex_t _field_mutex;
//pthread_mutex_t _initialized_mutex; // prove this is meaningful
pthread_mutex_t _spriteCount_mutex;
pthread_mutex_t _spriteCountMax_mutex;

bool initFieldMgr() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	if(_initialized) return false;

	pthread_mutex_init(&_field_mutex, NULL);
	//pthread_mutex_init(&_initialized_mutex, NULL);
	pthread_mutex_init(&_spriteCount_mutex, NULL);
	pthread_mutex_init(&_spriteCountMax_mutex, NULL);

	//pthread_mutex_lock(&_initialized_mutex);
		_initialized = true;
	//pthread_mutex_unlock(&_initialized_mutex);
	struct timeval t;
	gettimeofday(&t, NULL);
	srand(t.tv_sec ^ t.tv_usec);
	initField(SPRITECOUNTMAX_DEFAULT);
	return true;
}

int initField(int count) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, count);
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
	debugprint(LOG_INFO, DBGFORM"created _field with %d items\n", DBGSPEC, count);
	return retval;
}

bool purgeField() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
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
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	int sprCount = getSpriteCount();
	for(int i=0; i<sprCount; i++) {
		free(_field[i]);
		_field[i] = NULL;
	}
	setSpriteCount(0);
	return true;
}

int getSpriteCount() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	int retval = 0;
	pthread_mutex_lock(&_spriteCount_mutex);
		retval = getSpriteCountUnsafe();
	pthread_mutex_unlock(&_spriteCount_mutex);
	return retval;
}

int getSpriteCountMax() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	int retval = 0;
	pthread_mutex_lock(&_spriteCountMax_mutex);
		retval = getSpriteCountMaxUnsafe();
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	return retval;
}

int setSpriteCount(int count) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, count);
	if(count < 0) return -1;
	int retval = 0;
	pthread_mutex_lock(&_spriteCount_mutex);
		retval = setSpriteCountUnsafe(count);
	pthread_mutex_unlock(&_spriteCount_mutex);
	return retval;
}

int setSpriteCountMax(int count) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, count);
	if(count <= 0) return -1;
	int retval = 0;
	pthread_mutex_lock(&_spriteCountMax_mutex);
		retval = setSpriteCountMaxUnsafe(count);
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	return retval;
}

int getSpriteCountUnsafe() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	return _spriteCount;
}

int getSpriteCountMaxUnsafe() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	return _spriteCountMax;
}

int setSpriteCountUnsafe(int count) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, count);
	_spriteCount = count;
	return count;
}

int setSpriteCountMaxUnsafe(int count) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, count);
	_spriteCountMax = count;
	return count;
}

bool addRandoToField() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	pthread_mutex_lock(&_field_mutex);
		int sprCount = getSpriteCount();
		int sprMax = getSpriteCountMax();
		if(sprCount >= sprMax) {
			pthread_mutex_unlock(&_field_mutex);
			return false;
		}
		//Sprite* myNewSprite = malloc(sizeof(Sprite));
		char bsname[16] = "";
		sprintf(bsname, "poppycock%d", rand()%999);
		Sprite* myNewSprite = getPHSprite(bsname, 100.f, 200.f);
		_field[sprCount] = myNewSprite;
		debugprint(LOG_INFO, DBGFORM"_field[%d].identity is %s\n", DBGSPEC,
			sprCount, myNewSprite->identity);
		sprCount++;
		setSpriteCount(sprCount);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

bool addSpriteToField(char* identity, char* type, double x, double y) {
	debugprint(LOG_DEBUG, DBGFORM"%s, %s, %f, %f\n", DBGSPEC, identity, type, x, y);
	// TODO: dereference type
	// make sure _field is not full
	pthread_mutex_lock(&_field_mutex);
		int sprCount = getSpriteCount();
		if(sprCount >= getSpriteCountMax()) {
			pthread_mutex_unlock(&_field_mutex);
			return false;
		}
		// make sure nothing with this identity is already present
		if(getSpriteByIdUnsafe(identity)) {
			pthread_mutex_unlock(&_field_mutex);
			return false;
		}
		// create Sprite
		Sprite* theNewSprite = getPHSprite(identity, 400.f, 200.f);
		// add to _field
		_field[sprCount] = theNewSprite;
		debugprint(LOG_INFO, DBGFORM"_field[%d].identity is %s; .anims.identity is %s\n", DBGSPEC,
				sprCount, _field[sprCount]->identity,
				_field[sprCount]->anims->identity);
		sprCount++;
		setSpriteCount(sprCount);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

int getSpriteIndexById(char* identity) {
	debugprint(LOG_DEBUG, DBGFORM"%s\n", DBGSPEC, identity);
	int retval = -1;
	pthread_mutex_lock(&_field_mutex);
		retval = getSpriteIndexByIdUnsafe(identity);
	pthread_mutex_unlock(&_field_mutex);
	return retval;
}

int getSpriteIndexByIdUnsafe(char* identity) {
	debugprint(LOG_DEBUG, DBGFORM"%s\n", DBGSPEC, identity);
	int retval = -1;
	for(int i=0; i<getSpriteCount() && retval == -1; i++) {
		if(strcmp(identity, _field[i]->identity)==0) {
			retval = i;
		}
	}
	return retval;
}

Sprite* getSpriteById(char* identity) {
	debugprint(LOG_DEBUG, DBGFORM"%s\n", DBGSPEC, identity);
	Sprite* retval = NULL;
	pthread_mutex_lock(&_field_mutex);
		retval = getSpriteByIdUnsafe(identity);
	pthread_mutex_unlock(&_field_mutex);
	return retval;
}

Sprite* getSpriteByIdUnsafe(char* identity) {
	debugprint(LOG_DEBUG, DBGFORM"%s\n", DBGSPEC, identity);
	Sprite* retval = NULL;
	int idx = getSpriteIndexByIdUnsafe(identity);
	if(idx >= 0) retval = _field[idx];
	return retval;
}

bool delSpriteById(char* identity) {
	debugprint(LOG_DEBUG, DBGFORM"%s\n", DBGSPEC, identity);
	bool retval = true;
	pthread_mutex_lock(&_field_mutex);
		retval = delSpriteByIdUnsafe(identity);
	pthread_mutex_unlock(&_field_mutex);
	makeContiguous();
	return retval;
}

bool delSpriteByIdUnsafe(char* identity) {
	debugprint(LOG_DEBUG, DBGFORM"%s\n", DBGSPEC, identity);
	int idx = getSpriteIndexByIdUnsafe(identity);
	return delSpriteByIndexUnsafe(idx);
}

bool delSpriteByIndex(int idx) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, idx);
	bool retval = true;
	pthread_mutex_lock(&_field_mutex);
		retval = delSpriteByIndexUnsafe(idx);
	pthread_mutex_unlock(&_field_mutex);
	makeContiguous();
	return retval;
}

bool delSpriteByIndexUnsafe(int idx) {
	debugprint(LOG_DEBUG, DBGFORM"%d\n", DBGSPEC, idx);
	if(idx > getSpriteCountMaxUnsafe()) return false;
	if(idx < 0) return false;
	if(_field[idx] == NULL) return false;
	debugprint(LOG_INFO, DBGFORM"killing %s, x=%f, y=%f\n", DBGSPEC,
		_field[idx]->identity, _field[idx]->pos_x, _field[idx]->pos_y);
	free(_field[idx]);
	_field[idx] = NULL;
	return true;
}

bool makeContiguous() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	bool retval;
	lockField();
		retval = makeContiguousUnsafe();
	unlockField();
	return retval;
}

bool makeContiguousUnsafe() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	int max = getSpriteCountMaxUnsafe();
	int oldCount = getSpriteCountUnsafe();
	int newCount = 0;
	Sprite** newField = malloc(sizeof(Sprite*)*max);
	for(int i=0; i<max; i++) {
		if(_field[i] != NULL) {
			newField[newCount] = _field[i];
			newCount++;
		}
	}
	if(newCount != oldCount) {
		free(_field);
		_field = newField;
		setSpriteCountUnsafe(newCount);
	}
	debugprint(LOG_INFO, DBGFORM"oldCount=%d, newCount=%d\n", DBGSPEC, oldCount, newCount);
	if(newCount != oldCount) return true;
	return false;
}

void lockField() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	pthread_mutex_lock(&_field_mutex);
	pthread_mutex_lock(&_spriteCount_mutex);
	pthread_mutex_lock(&_spriteCountMax_mutex);
}

void unlockField() {
	debugprint(LOG_DEBUG, DBGFORM"\n", DBGSPEC);
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	pthread_mutex_unlock(&_spriteCount_mutex);
	pthread_mutex_unlock(&_field_mutex);
}
