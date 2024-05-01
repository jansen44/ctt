#include "cli.h"

static int short_option(char *arg, struct ctt_cmds *cmds);

int init_cli(int argc, char **argv, struct ctt_cmds *cmds) {
  for (int i = 1; i < argc; i++) {
    char *curr = argv[i];
    if (curr[0] == '-') {
      int response = short_option(curr, cmds);
      if (response != 0) {
        return i;
      }
    }
  }

  return 0;
}

static int short_option(char *arg, struct ctt_cmds *cmds) {
  int j = 1;
  while (arg[j] != '\0') {
    switch (arg[j]) {
    case 'c':
      cmds->should_complete = 1;
      break;
    default:
      return 1;
      break;
    };

    j++;
  }
  return 0;
}
