#ifndef DEBUG_H
#define DEBUG_H

#if !defined LOGLEVEL
#define LOGLEVEL 2
#endif

#define DBGFORM "%24s: %24s: "
#define DBGSPEC __FILE__, __FUNCTION__

// increasing order of verbosity
#define LOG_ERROR 0
#define LOG_WARN  1
#define LOG_INFO  2
#define LOG_DEBUG 3

int debugprint(int level, const char * restrict format, ...);

#endif //DEBUG_H
