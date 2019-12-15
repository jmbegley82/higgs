#include <stdlib.h>
#include <assert.h>
#include "FieldMgr.h"

int main(int argc, char** argv) {
	initFieldMgr();
	initField(32);
	while(addRandoToField());  // should happen 32 times
	purgeField();
	while(addRandoToField());
	purgeField();
	addSpriteToField("Terra", "terra", 200.f, 200.f);
	Sprite* ass = getSpriteById("Terra");
	assert(ass != NULL);
	Sprite* balls = getSpriteById("Nonexist");
	assert(balls == NULL);
	int taint = getSpriteIndexById("Terra");
	assert(taint != -1);
	int grundle = getSpriteIndexById("Nonexist");
	assert(grundle == -1);
	bool failboat = addSpriteToField("Terra", "terra", 400.f, 300.f);
	assert(!failboat);
	assert(getSpriteById("Terra")->pos_y == 200.f);
	delSpriteByIndex(0);
	assert(getSpriteCount() == 0);
	return 0;
}
