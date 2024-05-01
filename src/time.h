#ifndef _CTT_TIME_
#define _CTT_TIME_

#include <time.h>

long time_diff_min(struct timespec *start, struct timespec *end);
long time_diff_s(struct timespec *start, struct timespec *end);
long time_diff_ms(struct timespec *start, struct timespec *end);

#endif
