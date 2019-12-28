#include <stdio.h>
#include <stdarg.h>
#include "Debug.h"

int debugprint(int level, const char * restrict format, ...) {
	int retval = 0;
	if(level <= LOGLEVEL) {
		va_list args;
		va_start(args, format);
		retval = vprintf(format, args);
		va_end(args);
	}
	return retval;
}

