#include "debug.h"

#include <stdio.h>
#include <stdarg.h>

static const char* NAMES[] = {
    "NONE",
    "CRIT",
    "ERR ",
    "INFO",
    "DBG ",
    "SPAM"
};

void _debug_tr_log(const char* file, int line, int level, const char* msg, ...) {
    va_list argptr;
    va_start(argptr, msg);
    const char *lvl = (level <= LOG_LEVEL_SPAM) ? NAMES[level] : "####";
    fprintf(stderr, "%s:%d %s: ", file, line, lvl);
    vfprintf(stderr, msg, argptr);
    fprintf(stderr, "\n");
    va_end(argptr);
}
