#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char **argv) {
  int nb_int = sizeof(int)*8;
  int nb_short = sizeof(short)*8;
  int nb_long = sizeof(long)*8;
  int nb_long_long = sizeof (long long)*8;
  int nb_int8 = sizeof(int8_t)*8;
  int nb_int16 = sizeof(int16_t)*8;
  int nb_int32 = sizeof(int32_t)*8;
  int nb_int64 = sizeof(int64_t)*8;
  printf("%-12s: %2d\n", "int", nb_int);
  printf("%-12s: %2d\n", "short", nb_short);
  printf("%-12s: %2d\n", "long", nb_long);
  printf("%-12s: %2d\n", "long long", nb_long_long);
  printf("%-12s: %2d\n", "int8", nb_int8);
  printf("%-12s: %2d\n", "int16", nb_int16);
  printf("%-12s: %2d\n", "int32", nb_int32);
  printf("%-12s: %2d\n", "int64", nb_int64);
  printf("Format for int64_t is %%%s\n", PRId64);
  return 0;
}

