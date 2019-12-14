#include <stdlib.h>
#include <assert.h>
#include "FieldMgr.h"

int main(int argc, char** argv) {
	initFieldMgr();
	initField(512);
	while(addRandoToField());  // should happen 512 times
	purgeField();
	while(addRandoToField());
	purgeField();
	addSpriteToField("terra", "Terra", 200.f, 200.f);
	Sprite* ass = getSpriteById("Terra");
	assert(ass != NULL);
	Sprite* balls = getSpriteById("Nonexist");
	assert(balls == NULL);
	int taint = getSpriteIndexById("Terra");
	assert(taint != -1);
	int grundle = getSpriteIndexById("Nonexist");
	assert(grundle == -1);
	bool failboat = addSpriteToField("terra", "Terra", 400.f, 300.f);
	assert(!failboat);
	assert(getSpriteById("Terra")->pos_y == 200.f);
	return 0;
}
