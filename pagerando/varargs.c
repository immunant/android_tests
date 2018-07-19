#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int ext_int = 1;
char* ext_str = "testing";

void simple(const char *format, ...) {
  char buffer[100];
  va_list va;
  va_start(va, format);
  vsnprintf(buffer, 100, format, va);
  va_end(va);
  printf("%s\n", buffer);
}

void multiple_starts(const char *format, ...) {
  char buffer1[100];
  char buffer2[100];
  va_list va;
  va_start(va, format);
  vsnprintf(buffer1, 100, format, va);
  va_end(va);
  va_start(va, format);
  vsnprintf(buffer2, 100, format, va);
  va_end(va);
  printf("%s\n", buffer1);
  printf("%s\n", buffer2);
}

void multiple_starts2(int control, const char *format, ...) {
  char buffer1[100];
  char buffer2[100];
  va_list va;
  va_start(va, format);
  vsnprintf(buffer1, 100, format, va);
  va_end(va);
  if (control) {
    va_start(va, format);
    vsnprintf(buffer2, 100, format, va);
    va_end(va);
  } else {
    strcpy(buffer2, "foobar");
  }
  printf("%s\n", buffer1);
  printf("%s\n", buffer2);
}


void copy(const char *format, ...) {
  char buffer1[100];
  char buffer2[100];
  va_list va, va2;
  va_start(va, format);
  va_copy(va2, va);
  vsnprintf(buffer1, 100, format, va);
  va_end(va);
  vsnprintf(buffer2, 100, format, va2);
  va_end(va2);
  printf("%s\n", buffer1);
  printf("%s\n", buffer2);
}


__attribute__ ((constructor))
static void run_varargs() {
  printf("**simple**\n");
  simple("ext_int: %i", ext_int);
  simple("ext_int: %i, str: %s", ext_int, ext_str);
  printf("**multiple_starts**\n");
  multiple_starts("ext_int: %i", ext_int);
  multiple_starts("ext_int: %i, str: %s", ext_int, ext_str);
  printf("**multiple_starts2**\n");
  multiple_starts2(1, "ext_int: %i", ext_int);
  multiple_starts2(0, "ext_int: %i, str: %s", ext_int, ext_str);
  printf("**copy**\n");
  copy("ext_int: %i", ext_int);
  copy("ext_int: %i, str: %s", ext_int, ext_str);
}
