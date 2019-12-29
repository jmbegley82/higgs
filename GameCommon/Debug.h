#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>

#if !defined DEFAULT_LOGLEVEL
#define DEFAULT_LOGLEVEL 0
#endif

#define DBGFORM "%24s: %24s: "
#define DBGSPEC __FILE__, __FUNCTION__

// increasing order of verbosity
#define LOG_ERROR 0
#define LOG_WARN  1
#define LOG_INFO  2
#define LOG_DEBUG 3

bool initDebug();
int getLoglevel();
void setLoglevel(unsigned int level);
int lprintf(int level, const char * restrict format, ...);

#endif //DEBUG_H
