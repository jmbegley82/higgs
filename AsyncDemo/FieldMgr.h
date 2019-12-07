#ifndef FIELDMGR_H
#define FIELDMGR_H

typedef struct {
	char identity[16];
	double x;
	double y;
	double w;
	double h;
} Cel;

Cel* getRenderList();

#endif //FIELDMGR_H
