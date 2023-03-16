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
greeter(void* data){
  pthread_t id = *(pthread_t *)data;
  int64_t t = 0;
  for (int i=0; i<REPETITIONS; i++){
      t = utime();
      printf("Aloha! at %" PRId64 " from thread %p in %s v%s\n", t, id, PROJECT_NAME, PROJECT_VERSION);
      sleep(PERIOD);
  }
  return NULL; // TODO Is this really necessary?
}

int main(int argc, char **argv) {
  pthread_t greeter_thread;
  int greeter_thread_create_rc = pthread_create(&greeter_thread, NULL, greeter, (void *)&greeter_thread);
  if(greeter_thread_create_rc != 0) {
    perror("pthread_create");
  }

  pthread_join(greeter_thread, NULL);

  exit(EXIT_SUCCESS);
}
