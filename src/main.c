#include "config.h"

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline int64_t
utime(void)
{
  struct timespec t;
  clock_gettime( CLOCK_REALTIME, &t );
  return (int64_t)( t.tv_sec ) * 1000000 + (int64_t)( t.tv_nsec / 1000 );
}

int main(int argc, char **argv) {
  int64_t t = utime();
  printf("Aloha! at %" PRId64 " from %s in %s v%s\n", t, argv[0], PROJECT_NAME, PROJECT_VERSION);
  return EXIT_SUCCESS;
}
