#include <stdio.h>
#include <pthread.h>

static pthread_once_t once_control = PTHREAD_ONCE_INIT;

static void InitOnceImpl() {
  printf("in child\n");
}

static void InitOnce() {
  pthread_once(&once_control, &InitOnceImpl);
}

__attribute__ ((constructor))
static void run_pthread_fnpointer() {
  InitOnce();
}
