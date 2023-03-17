#ifndef _MAIN_H_
#define _MAIN_H_


#define LCM_QUEUE_CAPACITY 3
#define LCM_HANDLE_TIMEOUT 1000 // milliseconds

#define PERIOD 10000 // microseconds (for usleep in main thread)
#define REPETITIONS 1000

#define N_FOLLOWERS 7 // 7 same as # colors in ROYGBIV

#define ATTRACTOR_CHANNEL "A"
#define FOLLOWER_CHANNEL "F"

#include <inttypes.h>

#include <lcm/lcm.h>
#include <minmt_example_t.h>

static char* provider = NULL; // This is global so that all threads use the same LCM provider.

static inline int64_t utime(void);

typedef struct _follower_t {
  lcm_t* lcm;
  minmt_example_t* self;
} follower_t;
//^ For a truly minimal example, we could have avoided this by choosing a
//  problem that did not need to track any internal state.

static void follow(const lcm_recv_buf_t* rbuf, const char* channel, const minmt_example_t* rx, void* user);
static void* follower_loop(void* data);

#endif // _MAIN_H_
