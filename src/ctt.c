#include "time.h"
#include <stdio.h>
#include <unistd.h>

int main() {
  struct timespec start, stop;

  clock_gettime(CLOCK_MONOTONIC, &start);
  sleep(120);
  clock_gettime(CLOCK_MONOTONIC, &stop);

  long min_diff = time_diff_min(&start, &stop);
  long sec_diff = time_diff_s(&start, &stop);
  long ms_diff = time_diff_ms(&start, &stop);

  printf("Elapsed (min): %ld min\n", min_diff);
  printf("Elapsed (sec): %ld sec\n", sec_diff);
  printf("Elapsed (msec): %ld msec\n", ms_diff);

  return 0;
}
