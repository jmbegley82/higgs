#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "FieldMgr.h"

pthread_mutex_t holdUp;

Cel* getRenderList() {
	Cel* retval = NULL;
	pthread_mutex_lock(&holdUp);
	retval = malloc(sizeof(Cel));
	strcpy(retval[0].identity, "whatever");
	retval[0].x = 100;
	retval[0].y = 100;
	retval[0].w = 400;
	retval[0].h = 400;
	pthread_mutex_unlock(&holdUp);
	return retval;
}
