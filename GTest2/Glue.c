#include "stdio.h"
#include "Cel.h"
#include "CelSet.h"
#include "AnimationSet.h"
#include "Glue.h"

Cel* loadCelFromFile(const char* path) {
	Cel* retval = NULL;
	// first validate path, make sure path ends in .png

	// then try to open it

	// if it exists, load it, register it, get its index number
	// and set img, width, height, offset_x and offset_y 

	// (if it existed) strip the .png from the end, add .cel
	// and try to load offset_x and offset_y from it
	return retval;
}

CelSet* loadCelSetFromPath(const char* path) {
	CelSet* retval = NULL;
	// validate the path

	// make sure the last section of the path is one of the
	// approved CelSet names (in GameCommon/CelSet.c)
	// if it's not, we will be returning a NULL

	// get a name-sorted list of the filenames within path that
	// end in .png; fill cels with Cels from loadCelFromFile

	// check for presence of $path/index.set and derive delay,
	// timeTilFlip and/or currentFrame from it
	return retval;
}

AnimationSet* loadAnimationSetFromPath(const char* path) {
	AnimationSet* retval = NULL;
	// validate the path

	// set identity to the last segment of path

	// for every subdirectory, loadCelSetFromPath it and add
	// the resulting CelSets to sets

	// check for $path/index.aset
	return retval;
}
