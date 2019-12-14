#include "FieldMgr.h"

int main(int argc, char** argv) {
	initFieldMgr();
	initField(512);
	while(addRandoToField());  // should happen 512 times
	return 0;
}
