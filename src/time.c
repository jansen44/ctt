#include "time.h"

long time_diff_min(struct timespec *start, struct timespec *end) {
  return (end->tv_sec - start->tv_sec) / 60;
}

long time_diff_s(struct timespec *start, struct timespec *end) {
  return (end->tv_sec - start->tv_sec);
}

long time_diff_ms(struct timespec *start, struct timespec *end) {
  return ((end->tv_sec - start->tv_sec) * 1000) +
         ((end->tv_nsec - start->tv_nsec) / 1000000);
}
