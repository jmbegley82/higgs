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
//pthread_mutex_t _initialized_mutex; // prove this is meaningful
pthread_mutex_t _spriteCount_mutex;
pthread_mutex_t _spriteCountMax_mutex;

//Sprite-related:
/*
Cel phc[] = {{4, 0.f, 1.f, 2.f, 3.f},
	    {5, 0.f, 1.f, 2.f, 3.f},
	    {6, 0.f, 1.f, 2.f, 3.f}};
CelSet phcs[] = {{"defaultcs", (Cel**)&phc, 5.f, 0, 1},
		 {"otherone",  (Cel**)&phc, 7.f, 0, 1}};
AnimationSet phas = {"default", 1, (CelSet**)phcs};
*/

char* phcsid = "ph celset";
char* phasid = "ph animset";

Cel* getPHCel(Image img, double width, double height, double offset_x, double offset_y) {
	Cel* retval = malloc(sizeof(Cel));
	retval->img = img;
	retval->width = width;
	retval->height = height;
	retval->offset_x = offset_x;
	retval->offset_y = offset_y;
	return retval;
}

CelSet* getPHCelSet(char* identity, double speed, unsigned int frameCount) {
	CelSet* retval = malloc(sizeof(CelSet));
	retval->identity = identity;
	retval->cels = malloc(sizeof(Cel)*frameCount);
	for(int i=0; i<frameCount; i++) {
		retval->cels[i] = getPHCel(i, 20.f, 20.f, -10.f, -10.f);
	}
	retval->speed = speed;
	retval->currentFrame = 0;
	retval->frameCount = frameCount;
	return retval;
}

AnimationSet* getPHAnimSet(char* identity, unsigned int setCount) {
	AnimationSet* retval = malloc(sizeof(AnimationSet));
	retval->identity = identity;
	retval->sets = malloc(sizeof(CelSet)*setCount);
	for(int i=0; i<setCount; i++) {
		retval->sets[i] = getPHCelSet(phcsid, 0.5f, 5);
	}
	retval->setCount = setCount;
	return retval;
}

Sprite* getPHSprite(char* identity, unsigned int animCount, double pos_x, double pos_y) {
	Sprite* retval = malloc(sizeof(Sprite));
	strcpy(retval->identity, identity);
	retval->anims = malloc(sizeof(AnimationSet)*animCount);
	for(int i=0; i<animCount; i++) {
		retval->anims[i] = getPHAnimSet(phasid, 5);
	}
	retval->pos_x = pos_x;
	retval->pos_y = pos_y;
	return retval;
}

/*
bool getPlaceholderAnim(AnimationSet* cs) {
	cs->identity = phas.identity;
	cs->sets = phas.sets;
	cs->setCount = phas.setCount;
	return true;
}

void newSprite(Sprite* sprite, char* identity, char* animSet, char* anim, double x, double y) {
	strcpy(sprite->identity, identity);
	//ignore animSet for now
	//ignore anim for now and use placeholder
	getPlaceholderAnim(&sprite->anims);
	sprite->pos_x = x;
	sprite->pos_y = y;
}
*/

//Field-related:
bool initFieldMgr() {
	if(_initialized) return false;

	pthread_mutex_init(&_field_mutex, NULL);
	//pthread_mutex_init(&_initialized_mutex, NULL);
	pthread_mutex_init(&_spriteCount_mutex, NULL);
	pthread_mutex_init(&_spriteCountMax_mutex, NULL);

	//pthread_mutex_lock(&_initialized_mutex);
		_initialized = true;
	//pthread_mutex_unlock(&_initialized_mutex);

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
		//Sprite* myNewSprite = malloc(sizeof(Sprite));
		char bsname[16] = "";
		sprintf(bsname, "poppycock%d", rand()%999);
		//newSprite(myNewSprite, bsname, "animset1", "anim1", 200.f, 200.f);
		Sprite* myNewSprite = getPHSprite(bsname, 5, 100.f, 200.f);
		_field[sprCount] = myNewSprite;
		printf("_field[%d].identity is %s\n", sprCount, myNewSprite->identity);
		sprCount++;
		setSpriteCount(sprCount);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

bool addSpriteToField(char* identity, char* type, double x, double y) {
	// dereference type (for now just pass to newSprite)
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
		//Sprite* theNewSprite = malloc(sizeof(Sprite));
		//newSprite(theNewSprite, identity, type, "default", x, y);
		Sprite* theNewSprite = getPHSprite(identity, 5, 400.f, 200.f);
		// add to _field
		_field[sprCount] = theNewSprite;
		printf("_field[%d].identity is %s; .anims.identity is %s\n", sprCount, _field[sprCount]->identity,
				_field[sprCount]->anims[0]->identity);
		sprCount++;
		setSpriteCount(sprCount);
	pthread_mutex_unlock(&_field_mutex);
	return true;
}

int getSpriteIndexById(char* identity) {
	int retval = -1;
	pthread_mutex_lock(&_field_mutex);
		retval = getSpriteIndexByIdUnsafe(identity);
	pthread_mutex_unlock(&_field_mutex);
	return retval;
}

int getSpriteIndexByIdUnsafe(char* identity) {
	int retval = -1;
	for(int i=0; i<getSpriteCount() && retval == -1; i++) {
		if(strcmp(identity, _field[i]->identity)==0) {
			retval = i;
		}
	}
	return retval;
}

Sprite* getSpriteById(char* identity) {
	Sprite* retval = NULL;
	pthread_mutex_lock(&_field_mutex);
		retval = getSpriteByIdUnsafe(identity);
	pthread_mutex_unlock(&_field_mutex);
	return retval;
}

Sprite* getSpriteByIdUnsafe(char* identity) {
	Sprite* retval = NULL;
	/*
	for(int i=0; i<getSpriteCount() && retval == NULL; i++) {
		if(strcmp(identity, _field[i]->identity)==0) {
			retval = _field[i];
		}
	}
	*/
	int idx = getSpriteIndexByIdUnsafe(identity);
	if(idx >= 0) retval = _field[idx];
	return retval;
}

bool delSpriteById(char* identity) {
	bool retval = true;
	pthread_mutex_lock(&_field_mutex);
		retval = delSpriteByIdUnsafe(identity);
	pthread_mutex_unlock(&_field_mutex);
	makeContiguous();
	return retval;
}

bool delSpriteByIdUnsafe(char* identity) {
	int idx = getSpriteIndexByIdUnsafe(identity);
	/*
	if(idx == -1) return false;
	free(_field[idx]);
	_field[idx] = NULL;
	return true;
	*/
	return delSpriteByIndexUnsafe(idx);
}

bool delSpriteByIndex(int idx) {
	bool retval = true;
	pthread_mutex_lock(&_field_mutex);
		retval = delSpriteByIndexUnsafe(idx);
	pthread_mutex_unlock(&_field_mutex);
	makeContiguous();
	return retval;
}

bool delSpriteByIndexUnsafe(int idx) {
	if(idx > getSpriteCountMaxUnsafe()) return false;
	if(idx < 0) return false;
	if(_field[idx] == NULL) return false;
	printf("delSpriteByIndexUnsafe:  killing %s, x=%f, y=%f\n", _field[idx]->identity, _field[idx]->pos_x,
			_field[idx]->pos_y);
	free(_field[idx]);
	_field[idx] = NULL;
	return true;
}

bool makeContiguous() {
	pthread_mutex_lock(&_field_mutex);
	pthread_mutex_lock(&_spriteCount_mutex);
	pthread_mutex_lock(&_spriteCountMax_mutex);
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
	pthread_mutex_unlock(&_spriteCountMax_mutex);
	pthread_mutex_unlock(&_spriteCount_mutex);
	pthread_mutex_unlock(&_field_mutex);
	printf("makeContiguous:  oldCount=%d, newCount=%d\n", oldCount, newCount);
	if(newCount != oldCount) return true;
	return false;
}
