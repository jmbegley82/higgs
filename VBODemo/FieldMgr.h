#ifndef FIELDMGR_H
#define FIELDMGR_H

typedef struct {
	char identity[16];
	double x;
	double y;
	double w;
	double h;
	// platform dependent and this non-serializable
	void* vboID;
	void* iboID;
	void* texID;
} Cel;

typedef struct {
	int count;
	Cel** cels;
} CelGroup;

/**
 * int initFieldMgr()
 * Initialized FieldMgr itself (needed to initialize its pthread_mutex)
 * Use this before anything else!  Also calls initField(FIELD_MAX).
 * Returns -1 if already initialized, otherwise returns maximum number
 * of objects in _field
 */
int initFieldMgr();

/**
 * int initField(int max)
 * Deletes _field if it exists, and recreates an empty one with #count items
 * This is a temporary function
 */
int initField(int max);

/**
 * Cel* getRenderList()
 * Returns an array of Cel structs to be used to draw the scene
 * Must be freed after use!
 */
Cel** getRenderList();

CelGroup getRenderGroup();

#endif //FIELDMGR_H
