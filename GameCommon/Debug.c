#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <pthread.h>
#include "Debug.h"


bool initialized = false;
int _loglevel = DEFAULT_LOGLEVEL;
pthread_mutex_t _loglevel_mutex;


bool initDebug() {
	if(initialized) return false;
	pthread_mutex_init(&_loglevel_mutex, NULL);
	initialized = true;
	return true;
}

int getLoglevel() {
	int retval = -1;
	pthread_mutex_lock(&_loglevel_mutex);
		retval = _loglevel;
	pthread_mutex_unlock(&_loglevel_mutex);
	return retval;
}

void setLoglevel(unsigned int level) {
	pthread_mutex_lock(&_loglevel_mutex);
		_loglevel = level;
	pthread_mutex_unlock(&_loglevel_mutex);
}

int lprintf(int level, const char * restrict format, ...) {
	int retval = 0;
	int logLevel = getLoglevel();
	if(level <= logLevel) {
		va_list args;
		va_start(args, format);
		retval = vprintf(format, args);
		//retval = lvprintf(level, format, args);
		va_end(args);
	}
	return retval;
}

int lvprintf(int level, const char * restrict format, va_list args) {
	int retval = 0;
	int logLevel = getLoglevel();
	if(level <= logLevel) {
		//va_list args;
		//va_start(args, format);
		retval = vprintf(format, args);
		//va_end(args);
	}
	return retval;
}

int errorprint(const char* restrict format, ...) {
	int retval = 0;
	va_list args;
	va_start(args, format);
	retval = lvprintf(LOG_ERROR, format, args);
	va_end(args);
	return retval;
}

int warnprint(const char* restrict format, ...) {
	int retval = 0;
	va_list args;
	va_start(args, format);
	retval = lvprintf(LOG_WARN, format, args);
	va_end(args);
	return retval;
}

int infoprint(const char* restrict format, ...) {
	int retval = 0;
	va_list args;
	va_start(args, format);
	retval = lvprintf(LOG_INFO, format, args);
	va_end(args);
	return retval;
}

int debugprint(const char* restrict format, ...) {
	int retval = 0;
	va_list args;
	va_start(args, format);
	retval = lvprintf(LOG_DEBUG, format, args);
	va_end(args);
	return retval;
}
