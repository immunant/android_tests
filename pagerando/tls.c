#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define NUM_THREADS 5

/* NOT SUPPORTED IN BIONIC
   __thread int global_tls; */

static pthread_key_t global_key;
 
/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;
 
/* thread function */
static void *thr_func(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  int *ptr;
  if ((ptr = pthread_getspecific(global_key)) == NULL) {
    ptr = malloc(sizeof(int));
    *ptr = data->tid;
    (void) pthread_setspecific(global_key, ptr);
  }
  printf("hello from thr_func, thread id: %d\n", data->tid);
  ptr = pthread_getspecific(global_key);
  printf("Found TLS value %d\n", *ptr);
 
  pthread_exit(NULL);
}

__attribute__ ((constructor))
static void run_tls() {
  pthread_t thr[NUM_THREADS];
  int i, rc;
  /* create a thread_data_t argument array */
  thread_data_t thr_data[NUM_THREADS];

  if ((rc = pthread_key_create(&global_key, NULL))) {
    fprintf(stderr, "error: pthread_key_create, rc: %d\n", rc);
    return;
  }

  /* create threads */
  for (i = 0; i < NUM_THREADS; ++i) {
    thr_data[i].tid = i;
    if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return;
    }
  }
  /* block until all threads complete */
  for (i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thr[i], NULL);
  }
 
  return;
}
