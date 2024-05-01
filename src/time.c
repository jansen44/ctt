#include "time.h"

struct fmt_time {
  int h;
  int m;
  int s;
  int ms;
};

static struct fmt_time fmt_from_s(time_t secs);

struct timespec now() {
  struct timespec nowspec;
  clock_gettime(CLOCK_REALTIME, &nowspec);
  return nowspec;
}

time_t now_in_millis() {
  struct timespec nowspec = now();
  return time_in_millis(&nowspec);
}

time_t time_in_millis(struct timespec *spec) {
  return spec->tv_sec * 1000 + spec->tv_nsec / 1000000;
}

time_t time_diff_min(time_t start, time_t end) {
  return time_diff_s(start, end) / 60;
}

/**
 * Gets two time_t in ms and return the diff in seconds
 **/
time_t time_diff_s(time_t start, time_t end) {
  return time_diff_ms(start, end) / 1000;
}

time_t time_diff_ms(time_t start, time_t end) { return end - start; }

void fmt_tm_to_str(struct tm *tm, char *dst) {
  sprintf(dst, "%02d/%02d/%04d - %02d:%02d:%02d", tm->tm_mday, tm->tm_mon,
          tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void fmt_secs_to_str(time_t secs, char *dst) {
  struct fmt_time fmt = fmt_from_s(secs);
  sprintf(dst, "%02d:%02d:%02d", fmt.h, fmt.m, fmt.s);
}

static struct fmt_time fmt_from_s(time_t secs) {
  struct fmt_time fmt_time = {
      .h = secs / 60 / 60,
      .m = (secs / 60) % 60,
      .s = secs % 60,
      .ms = 0,
  };
  return fmt_time;
}
