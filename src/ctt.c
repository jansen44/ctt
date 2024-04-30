#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
  struct timespec start, stop;

  clock_gettime(CLOCK_MONOTONIC, &start);
  sleep(1);
  clock_gettime(CLOCK_MONOTONIC, &stop);

  long sec_diff = (stop.tv_sec - start.tv_sec);
  long msec_diff = (stop.tv_nsec - start.tv_nsec) / 1000000;

  printf("Elapsed: %ld.%ld", sec_diff, msec_diff);

  return 0;
}
