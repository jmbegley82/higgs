#ifndef CEL_H
#define CEL_H

#include "Geometry.h"

typedef unsigned int Image;

typedef struct {
	Image img;			//index# of image to draw
	double width, height;		//self-explanatory
	double offset_x, offset_y;	//distance from center to left/top
} Cel;

Cel* newCel(Image img, double width, double height, double offset_x, double offset_y);

#endif //CEL_H
