#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "FieldMgr.h"
#include "CelSet.h"
#include "Geometry.h"
#include "Debug.h"

int main(int argc, char** argv) {
	initDebug();
	initFieldMgr();
	initField(32);
	while(addRandoToField());  // should happen 32 times
	purgeField();
	while(addRandoToField());
	purgeField();
	addSpriteToField("Terra", "terra", 200.f, 200.f);
	Sprite* tsprite = getSpriteById("Terra");
	assert(tsprite != NULL);
	Sprite* spr1 = getSpriteById("Nonexist");
	assert(spr1 == NULL);
	int tmpi = getSpriteIndexById("Terra");
	assert(tmpi != -1);
	int tmpj = getSpriteIndexById("Nonexist");
	assert(tmpj == -1);
	bool failboat = addSpriteToField("Terra", "terra", 400.f, 300.f);
	assert(!failboat);
	assert(getSpriteById("Terra")->pos_y == 200.f);
	//delSpriteByIndex(getSpriteIndexById("Terra"));
	Sprite* mysprite = getSpriteById("Terra");
	infoprint("%s %f\n", mysprite->anims->identity,
			  mysprite->anims->sets[0]->cels[0]->width); //;mysprite->anims.identity);
	QuadPoint qp = getQuad(mysprite);
	infoprint("(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n", qp.topLeft.x, qp.topLeft.y,
			qp.topRight.x, qp.topRight.y, qp.bottomLeft.x, qp.bottomLeft.y,
			qp.bottomRight.x, qp.bottomRight.y);
	CelSet* cs = getCurrentCelSet(mysprite->anims);
	infoprint("cs identity=%s\n", cs->identity);
	setPosition(mysprite, 500.f, 500.f);
	qp = getQuad(mysprite);
	infoprint("(%f,%f) (%f,%f) (%f,%f) (%f,%f)\n", qp.topLeft.x, qp.topLeft.y,
			qp.topRight.x, qp.topRight.y, qp.bottomLeft.x, qp.bottomLeft.y,
			qp.bottomRight.x, qp.bottomRight.y);
	cs = getCelSetById(mysprite->anims, "ph celset");
	infoprint("cs identity=%s\n", cs->identity);
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
	assert(getCSetTypeIndex("walkr")==2);
	infoprint("the '%s' tastes like debug\n", getCSetTypeString(25));
	AnimationSet* asset = newAnimationSet("whynot");
	infoprint("%s\n", asset->identity);
	debugprint("debugprint seems to work\n");
	infoprint("infoprint seems to work\n");
	warnprint("warnprint seems to work\n");
	errorprint("errorprint seems to work\n");
	return 0;
}
