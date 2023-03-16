#ifndef _MAIN_H_
#define _MAIN_H_

#define PERIOD 1e-2
#define REPETITIONS 21

#include <inttypes.h>

#include <lcm/lcm.h>


static inline int64_t utime(void);

static void random_walker(void* data);

#endif // _MAIN_H_
