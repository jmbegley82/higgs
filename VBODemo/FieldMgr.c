#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include "FieldMgr.h"

bool _initialized = false;
Cel** _field = NULL;
int _fieldCount = 0;
int _fieldCountMax = 0;
#define FIELD_MAX 20

pthread_mutex_t _holdUp;

int initFieldMgr() {
	if(_initialized) return -1;
	pthread_mutex_init(&_holdUp, NULL);
	_initialized = true;
	return initField(FIELD_MAX);
}

int initField(int max) {
	pthread_mutex_lock(&_holdUp);
	int saneMax = FIELD_MAX;
	if(max < saneMax) saneMax = max;

	if(saneMax <= 0) return -1;  //NO

	if(_field != NULL) {
		if(_fieldCount > 0) {
			for(int i=0; i<_fieldCount; i++) {
				free(_field[i]);
			}
		}
		free(_field);
	}

	_field = malloc(sizeof(Cel*)*saneMax);
	_fieldCountMax = saneMax;
	_fieldCount = 0;

	pthread_mutex_unlock(&_holdUp);
	return saneMax;
}

void cellCopy(Cel dest, Cel src) {
	strcpy(dest.identity, src.identity);
	dest.x = src.x;
	dest.y = src.y;
	dest.w = src.w;
	dest.h = src.h;
	dest.vboID = src.vboID;
	dest.iboID = src.iboID;
	dest.texID = src.texID;
}

bool addToField(const char* id, double x, double y, double w, double h, void* vbo, void* ibo, void* tex) {
	pthread_mutex_lock(&_holdUp);
	if(_fieldCount >= _fieldCountMax) {
		pthread_mutex_unlock(&_holdUp);
		return false;
	}
	// this is where we'd check for identity collision if we weren't terminally lazy
	// checks are done, go for it
	_fieldCount++;
	_field[_fieldCount] = malloc(sizeof(Cel));
	strcpy(_field[_fieldCount]->identity, id);
	_field[_fieldCount]->x = x;
	_field[_fieldCount]->y = y;
	_field[_fieldCount]->w = w;
	_field[_fieldCount]->h = h;
	_field[_fieldCount]->vboID = vbo;
	_field[_fieldCount]->iboID = ibo;
	_field[_fieldCount]->texID = tex;
	pthread_mutex_unlock(&_holdUp);
	return true;
}

Cel** getRenderList() {
	Cel** retval = NULL;
	pthread_mutex_lock(&_holdUp);
	if(_fieldCount > 0) {
		malloc(sizeof(Cel*)*_fieldCount);
		for(int i=0; i<_fieldCount; i++) {
			retval[i] = malloc(sizeof(Cel));
			cellCopy(*retval[i], *_field[i]);
			/*
			strcpy(retval[i]->identity, _field[i]->identity);
			retval[i]->x = _field[i]->x;
			retval[i]->y = _field[i]->y;
			retval[i]->w = _field[i]->w;
			retval[i]->h = _field[i]->h;
			retval[i]->vboID = _field[i]->vboID;
			retval[i]->iboID = _field[i]->iboID;
			retval[i]->texID = _field[i]->texID;
			*/
		}
	}
	pthread_mutex_unlock(&_holdUp);
	return retval;
}
