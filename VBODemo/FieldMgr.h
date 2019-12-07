#ifndef FIELDMGR_H
#define FIELDMGR_H

typedef struct {
	char identity[16];
	double x;
	double y;
	double w;
	double h;
} Cel;

/**
 * Cel* getRenderList()
 * Returns an array of Cel structs to be used to draw the scene
 * Must be freed after use!
 */
Cel* getRenderList();

#endif //FIELDMGR_H
