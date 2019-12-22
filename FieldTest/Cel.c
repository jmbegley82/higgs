//#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
//#include <pthread.h>
//#include <sys/time.h>

#include "Cel.h"

Cel* newCel(Image img, double width, double height, double offset_x, double offset_y) {
	Cel* retval = malloc(sizeof(Cel));
	retval->img = img;
	retval->width = width;
	retval->height = height;
	retval->offset_x = offset_x;
	retval->offset_y = offset_y;
	return retval;
}
