#ifndef GLUE_H
#define GLUE_H

#include "Cel.h"
#include "CelSet.h"
#include "AnimationSet.h"

/**
 * load individual Cel from file
 * path should point to a .png file.  optionally, a .cel file alongside the
 * specified .png file may be used to manually set offset_x and offset_y
 * width and height will always be set automatically
 */
Cel* loadCelFromFile(const char* path);

/**
 * load CelSet from path
 * path should point to a directory containing at least one .png file
 * directory may contain a text file named index.set, defining delay,
 * timeTilFlip and currentFrame.  frameCount is always calculated
 */
CelSet* loadCelSetFromPath(const char* path);

/**
 * load AnimationSet from path
 * path should point to a directory containing at least a subdirectory named
 * 'default' which should contain at least one .png file.  subdirectories
 * representing CelSets may be present, named after their respective types
 * (listed in GameCommon/CelSet.c).  directory may contain a text file named
 * index.aset defining currentSetIdx.
 */
AnimationSet* loadAnimationSetFromPath(const char* path);

/**
 * load Sprite from file
 * path should point to a text file
 * does Sprite even contain anything that would be best defined this way?
 */
//Sprite* loadSpriteFromFile(const char* path);

#endif //GLUE_H
