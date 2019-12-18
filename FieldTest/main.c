#include <stdlib.h>
#include <stdio.h>
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
	//delSpriteByIndex(getSpriteIndexById("Terra"));
	Sprite* myass = getSpriteById("Terra");
	printf("%s %f\n", myass->anims[0]->identity,
			  myass->anims[0]->sets[0]->cels[0]->width); //;myass->anims.identity);
	delSpriteById("Terra");
	assert(getSpriteCount() == 0);

	while(addRandoToField());
	delSpriteByIndexUnsafe(20);
	delSpriteByIndexUnsafe(10);
	delSpriteByIndexUnsafe(12);
	delSpriteByIndexUnsafe(13);
	delSpriteByIndexUnsafe(14);
	delSpriteByIndexUnsafe(15);
	makeContiguous();
	makeContiguous();
	purgeField();

	AnimationSet anim;
	anim.sets = malloc(sizeof(CelSet)*10);
	//anim.sets[8].cels = NULL;
	return 0;
}
