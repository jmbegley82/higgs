#include "FieldMgr.h"

int main(int argc, char** argv) {
	initFieldMgr();
	initField(512);
	while(addRandoToField());  // should happen 512 times
	purgeField();
	while(addRandoToField());
	purgeField();
	addSpriteToField("terra", "Terra", 200.f, 200.f);
	return 0;
}
