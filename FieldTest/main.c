#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "FieldMgr.h"
#include "CelSet.h"
#include "Geometry.h"

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
	printf("%s %f\n", myass->anims->identity,
			  myass->anims->sets[0]->cels[0]->width); //;myass->anims.identity);
	QuadPoint qp = getQuad(myass);
	printf("(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n", qp.topLeft.x, qp.topLeft.y,
			qp.topRight.x, qp.topRight.y, qp.bottomLeft.x, qp.bottomLeft.y,
			qp.bottomRight.x, qp.bottomRight.y);
	CelSet* cs = getCurrentCelSet(myass->anims);
	printf("cs identity=%s\n", cs->identity);
	setPosition(myass, 500.f, 500.f);
	qp = getQuad(myass);
	printf("(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n", qp.topLeft.x, qp.topLeft.y,
			qp.topRight.x, qp.topRight.y, qp.bottomLeft.x, qp.bottomLeft.y,
			qp.bottomRight.x, qp.bottomRight.y);
	cs = getCelSetById(myass->anims, "ph celset");
	printf("cs identity=%s\n", cs->identity);
	delSpriteById("Terra");
	assert(getSpriteCount() == 0);

	while(addRandoToField());
	// test some less-than-safe stuff
	lockField();
	delSpriteByIndexUnsafe(20);
	delSpriteByIndexUnsafe(10);
	delSpriteByIndexUnsafe(12);
	delSpriteByIndexUnsafe(13);
	delSpriteByIndexUnsafe(14);
	delSpriteByIndexUnsafe(15);
	makeContiguousUnsafe();
	unlockField();
	// ok that's enough unsafe stuff
	makeContiguous();
	purgeField();

	//AnimationSet anim;
	//anim.sets = malloc(sizeof(CelSet)*10);
	//anim.sets[8].cels = NULL;
	CelSet* csa = getPHCelSet("testee", 60.f, 20);
	tickCelSet(csa, 31.f);
	tickCelSet(csa, 30.f);
	tickCelSet(csa, 301.f);
	tickCelSet(csa, 1200.f);
	return 0;
}
