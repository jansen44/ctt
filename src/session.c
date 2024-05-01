#include "session.h"

sessionresp_t get_or_init_session(struct session *session) {
  char lock_path[MAX_PATH_SIZE] = {0};
  get_lock_path(lock_path, MAX_PATH_SIZE);

  struct lock lock = {0};
  int output = get_lock(lock_path, &lock);

  if (output == 0) {
    session->lock = lock;
    return SESSION_RETRIEVED;
  }

  if (init_lock(lock_path) != 0) {
    return ERR_CREATING_SESSION;
  }

  return SESSION_INITIALIZED;
}

void session_report(struct session *session) {
  time_t now = now_in_millis();
  time_t diff = time_diff_s(session->lock.created_at, now);

  char session_time_output[9] = {0};
  fmt_secs_to_str(diff, session_time_output);
  printf(":: Session Duration:\t\t%s\n", session_time_output);
}

int complete_session(struct session *session) {
  printf(":: Session Complete!\n");
  return 0;
}