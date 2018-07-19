#include <stdio.h>

int global = 0;
void (*global_fn_ptr)();


struct test_st {
  struct test_st* a;
  int b;
  int* arr;
};

int global_array[1000];
struct test_st global_st = { 0, 1, global_array };

int arr2[3];
struct test_st global_st2 = { &global_st, 2, arr2 };

void global_uncalled_fn() {
  printf("global uncalled\n");
  printf("Force non-trivial function\n");
}

int global_fn() {
  printf("global\n");
  printf("Force non-trivial function\n");
  return 1;
}

void var_arg_fn(int n_args, ...) {
  int x;
  va_list ap;
  va_start(ap, n_args);
  for (int i = 0; i < n_args; i++) {
    x = va_arg(ap, int);
    printf("%i\n", x);
  }
  va_end(ap);
}

void lots_of_args(int a, int b, int c, int d, int e, int f) {
  printf("%i, %i, %i, %i, %i, %i\n", a, b, c, d, e, f);
  printf("Force non-trivial function\n");
}

void __attribute__((weak))
weak_function() {
  printf("weak public fn\n");
  printf("Force non-trivial function\n");
}


static int static_fn() {
  printf("static\n");
  printf("Force non-trivial function\n");
  return 1;
}

static void static_var_arg_fn(int n_args, ...) {
  int x;
  va_list ap;
  va_start(ap, n_args);
  for (int i = 0; i < n_args; i++) {
    x = va_arg(ap, int);
    printf("%i\n", x);
  }
  va_end(ap);
}

static void static_lots_of_args(int a, int b, int c, int d, int e, int f) {
  printf("%i, %i, %i, %i, %i, %i\n", a, b, c, d, e, f);
  printf("Force non-trivial function\n");
}

__attribute__ ((constructor))
static void constructor() {
  printf("In constructor()\n");
  global_fn();
  var_arg_fn(2, 1, 2);
  lots_of_args(1,2,3,4,5,6);
  weak_function();
  static_fn();
  static_var_arg_fn(1, 2, 3);
  static_lots_of_args(1,2,3,4,5,6);
}

__attribute__ ((destructor))
static void destructor() {
  printf("In destructor\n");
  printf("Force non-trivial function\n");
}


/*****************************************************************************
Test visibility
*****************************************************************************/

__attribute__((visibility("default")))
int visibility_default() {
  printf("visibility default\n");
  printf("Force non-trivial function\n");
  return 1;
}

__attribute__((visibility("hidden")))
int visibility_hidden() {
  printf("visibility hidden\n");
  printf("Force non-trivial function\n");
  return 1;
}

__attribute__((visibility("protected")))
int visibility_protected() {
  printf("visibility protected\n");
  printf("Force non-trivial function\n");
  return 1;
}

__attribute__((visibility("internal")))
int visibility_internal() {
  printf("visibility internal\n");
  printf("Force non-trivial function\n");
  return 1;
}
