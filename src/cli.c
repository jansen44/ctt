#include "cli.h"

static int short_option(char *arg, struct ctt_cmds *cmds);
static int long_option(char *arg, struct ctt_cmds *cmds);

int init_cli(int argc, char **argv, struct ctt_cmds *cmds) {
  for (int i = 1; i < argc; i++) {
    char *curr = argv[i];
    size_t curr_len = strlen(curr);

    if (curr_len < 2) {
      return i;
    }

    if (curr[0] == '-' && curr[1] == '-') {
      int response = long_option(curr, cmds);
      if (response != 0) {
        return i;
      }

    } else if (curr[0] == '-' && curr[1] != '-') {
      int response = short_option(curr, cmds);
      if (response != 0) {
        return i;
      }
    }
  }

  return 0;
}

static int long_option(char *arg, struct ctt_cmds *cmds) {
  if (strcmp(arg, "--history") == 0) {
    cmds->show_history = 1;
  } else {
    return 1;
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
