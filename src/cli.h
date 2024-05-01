#ifndef _CTT_CLI_
#define _CTT_CLI_

struct ctt_cmds {
  int should_complete;
};

int init_cli(int argc, char **argv, struct ctt_cmds *cmds);

#endif
