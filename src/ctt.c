#include "lock.h"
#include "os.h"
#include "time.h"

#include <stdio.h>

int main() {
  if (initialize_ctt_dirs() != 0) {
    perror("ERR: Could not initialize dirs");
    return 1;
  }

  struct lock lock;
  lockresp_t lockresp = get_or_create_lock(&lock);
  if (lockresp == ERR_CREATING_LOCK) {
    printf(":: [ERR(%d)] Could not create lock file!\n", errno);
    return errno;
  }

  if (lockresp == LOCK_CREATED) {
    printf(":: Lockfile Initialized\n");
    return 0;
  }

  time_t now = now_in_millis();
  time_t diff = time_diff_s(lock.created_at, now);

  char time_out[11];
  fmt_secs_to_str(diff, time_out);

  printf(":: Lockfile created for:\t%s\n", time_out);
  return 0;
}
