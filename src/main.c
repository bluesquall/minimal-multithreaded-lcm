#include "config.h"

#include "main.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static inline int64_t
utime(void)
{
  struct timespec t;
  clock_gettime( CLOCK_REALTIME, &t );
  return (int64_t)( t.tv_sec ) * 1000000 + (int64_t)( t.tv_nsec / 1000 );
}

static void*
follow (void* data){
  int n = *(int *)data;
  int64_t t = 0;
  for (int i=0; i<REPETITIONS; i++) {
      t = utime();
      printf("Aloha! at %" PRId64 " from thread %d in %s v%s\n", t, n, PROJECT_NAME, PROJECT_VERSION);
      sleep(PERIOD);
  }
  return NULL; // TODO Is this really necessary?
}

int main(int argc, char **argv) {
  int _rc = 0;
  pthread_t follower[N_FOLLOWERS];

  for (int i=0; i<N_FOLLOWERS; i++) {
    _rc = pthread_create(&follower[i], NULL, follow, (void *)&i);
    if (_rc != 0) {
        perror("pthread_create");
    }
  }

  for (int i=0; i<N_FOLLOWERS; i++) {
    pthread_join(follower[i], NULL);
  }

  exit(EXIT_SUCCESS);
}
