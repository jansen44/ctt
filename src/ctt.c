#include "cli.h"
#include "lock.h"
#include "os.h"
#include "time.h"

#include <stdio.h>

int main(int argc, char **argv) {
  struct ctt_cmds cmds = {0};
  int cli_err = init_cli(argc, argv, &cmds);
  if (cli_err != 0) {
    printf(":: [ERR] Invalid arg: \"%s\"\n", argv[cli_err]);
    return 1;
  }

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
    printf(":: Session Initialized\n");
    return 0;
  }

  time_t now = now_in_millis();
  time_t diff = time_diff_s(lock.created_at, now);

  char time_out[11] = {0};
  fmt_secs_to_str(diff, time_out);

  printf(":: Session Duration:\t%s\n\n", time_out);

  if (!cmds.should_complete) {
    printf(":: If you want to complete your session, run \"ctt -c\"\n");
    return 0;
  }

  printf(":: Completing...\n");
  return 0;
}
