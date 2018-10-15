#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>

#define DBG if(
#define WTH )
#define PRNT printf(
#define GBD );

bool assert(int, int);

#endif