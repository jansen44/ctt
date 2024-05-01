#ifndef _CTT_TIME_
#define _CTT_TIME_

#include <stdio.h>
#include <string.h>
#include <time.h>

struct timespec now();
time_t now_in_millis();

time_t time_in_millis(struct timespec *spec);

time_t time_diff_min(time_t start, time_t end);
time_t time_diff_s(time_t start, time_t end);
time_t time_diff_ms(time_t start, time_t end);

void fmt_secs_to_str(time_t secs, char *dst);

#endif
