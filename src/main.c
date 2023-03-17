#include "config.h"

#include "main.h"

#include <math.h>
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

static void lprint(const lcm_recv_buf_t* rbuf,
          const char* channel,
          const minmt_example_t* rx,
          void* user){
  fprintf(stderr, "lprint\n");
  lcm_t* lcm = (lcm_t*)(user);

  minmt_example_t_publish(lcm, FOLLOWER_CHANNEL, rx);
}

static void
follow(const lcm_recv_buf_t* rbuf,
          const char* channel,
          const minmt_example_t* rx,
          void* user){
  follower_t* f = (follower_t*)(user);
  lcm_t* lcm = (lcm_t*)(f->lcm);
  minmt_example_t* self = (minmt_example_t*)(f->self);

  double delta=0.0, step=1.0;

  for (int dof = 0; dof < 2; dof++) {
      delta = rx->position[dof] - self->position[dof];
      self->position[dof] += copysign(delta, step);
  }

  // TODO if self->position is within capture radius, disable self

  // TODO consider publishing on different channels
  minmt_example_t_publish(lcm, FOLLOWER_CHANNEL, self);
}

static void*
follower_loop (void* data){
  int handled = 1;
  int n = *(int *)data;
  int64_t t = 0;

  follower_t follower = { 0 };

  lcm_t* lcm = lcm_create(provider);
  if (!lcm) {
    pthread_exit(NULL); // TODO EXIT_FAILURE?
  }

  minmt_example_t self = { 0 };

  follower.lcm = lcm;
  follower.self = &self;

//  minmt_example_t_subscription_t* _sub = minmt_example_t_subscribe(lcm, ATTRACTOR_CHANNEL, &lprint, (void*)(lcm));

  minmt_example_t_subscription_t* sub = minmt_example_t_subscribe(lcm, ATTRACTOR_CHANNEL, &follow, (void*)(&follower));
  minmt_example_t_subscription_set_queue_capacity(sub, LCM_QUEUE_CAPACITY);

  while(handled > 0) { // TODO consider using minmt_example_t->enabled to signal time to close the thread
    handled = lcm_handle_timeout(lcm, LCM_HANDLE_TIMEOUT);
  }

  lcm_destroy(lcm);
  return NULL; // TODO Is this really necessary?
}

int main(int argc, char **argv) {

  provider = getenv("LCM_DEFAULT_URL");
  if(provider) {
    printf("using LCM provider %s\n", provider);
  } else {
    printf("using LCM provider NULL\n");
  }

  lcm_t* lcm = lcm_create(provider);
  if (!lcm) {
    exit(EXIT_FAILURE);
  }

  minmt_example_t attractor = { 0 };
  attractor.enabled = 1;
  attractor.position[0] = 2.5;
  attractor.position[1] = -3.5;
  // attractor.color = minmt_colors_t.INFRARED;

  int _rc = 0;
  pthread_t follower[N_FOLLOWERS];

  for (int i=0; i<N_FOLLOWERS; i++) {
    _rc = pthread_create(&follower[i], NULL, follower_loop, (void *)&i);
    if (_rc != 0) {
        perror("pthread_create");
    }
  }

  for (int i=0; i<REPETITIONS; i++) {
    usleep(PERIOD);
    minmt_example_t_publish(lcm, ATTRACTOR_CHANNEL, &attractor);
  }

  for (int i=0; i<N_FOLLOWERS; i++) {
    pthread_join(follower[i], NULL);
  }

  exit(EXIT_SUCCESS);
}
