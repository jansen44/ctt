#include "cli.h"
#include "os.h"
#include "session.h"

#include <stdio.h>

int main(int argc, char **argv) {
  struct ctt_cmds cmds = {0};
  int cli_err = init_cli(argc, argv, &cmds);
  if (cli_err != 0) {
    fprintf(stderr, ":: [ERR] Invalid arg: \"%s\"\n", argv[cli_err]);
    return 1;
  }

  if (cmds.show_history) {
    int output = show_session_history();
    if (output == ERR_HISTORY_FILE_NOT_FOUND) {
      fprintf(stderr, ":: [ERR]: History uninitialized! Have you completed any "
                      "session yet?\n");
      return ERR_HISTORY_FILE_NOT_FOUND;
    } else if (output != 0) {
      fprintf(stderr, ":: [ERR(%d)]: Something went wrong\n", output);
      return output;
    }
    return 0;
  }

  if (initialize_ctt_dirs() != 0) {
    fprintf(stderr, "[ERR]: Could not initialize dirs");
    return 1;
  }

  struct session session;
  sessionresp_t sessionresp = get_or_init_session(&session);
  if (sessionresp == ERR_CREATING_SESSION) {
    perror(":: [ERR] Could not initialize session: ");
    return errno;
  }

  if (sessionresp == SESSION_INITIALIZED) {
    printf(":: Session Initialized.\n");
    return 0;
  }

  session_report(&session);
  if (cmds.should_complete) {
    return complete_session(&session);
  }

  printf(":: If you want to complete your session, run \"ctt -c\"\n");

  return 0;
}
