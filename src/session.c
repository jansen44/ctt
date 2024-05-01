#include "session.h"

static time_t session_duration(struct session *session, time_t *now);

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
  time_t duration = session_duration(session, NULL);

  char session_time_output[9] = {0};
  fmt_secs_to_str(duration, session_time_output);

  // localtime_r works with secs, not ms
  long created_at_s = session->lock.created_at / 1000;
  struct tm created_at_tm = {0};
  localtime_r(&created_at_s, &created_at_tm);

  char session_init_time_output[22] = {0};
  fmt_tm_to_str(&created_at_tm, session_init_time_output);

  printf(":: Session Initialized at: %s\n", session_init_time_output);
  printf(":: Session Duration:\t\t\t%s\n", session_time_output);
}

int complete_session(struct session *session) {
  char history_path[MAX_PATH_SIZE] = {0};
  get_history_path(history_path, MAX_PATH_SIZE);

  time_t finished_at = now_in_millis();
  time_t duration = session_duration(session, &finished_at);
  struct history_item history_item = {
      .initialized_at = session->lock.created_at,
      .finished_at = finished_at,
      .duration = duration,
  };

  int append_result = append_history_item(history_path, &history_item);
  if (append_result != 0) {
    return append_result;
  }

  destroy_lock();
  printf(":: Session Complete!\n");
  return 0;
}

int show_session_history() {
  struct history history = {0};
  char history_path[MAX_PATH_SIZE] = {0};
  get_history_path(history_path, MAX_PATH_SIZE);

  int output = get_history(history_path, &history);
  if (output != 0) {
    return output;
  }

  for (int i = 0; i < history.history_len; i++) {
    struct history_item curr = history.items[i];

    time_t duration = curr.duration;
    char session_time_output[9] = {0};
    fmt_secs_to_str(duration, session_time_output);

    long created_at_s = curr.initialized_at / 1000;
    struct tm created_at_tm = {0};
    localtime_r(&created_at_s, &created_at_tm);
    char session_init_time_output[22] = {0};
    fmt_tm_to_str(&created_at_tm, session_init_time_output);

    long finished_at_s = curr.finished_at / 1000;
    struct tm finished_at_tm = {0};
    localtime_r(&finished_at_s, &finished_at_tm);
    char session_finished_time_output[22] = {0};
    fmt_tm_to_str(&finished_at_tm, session_finished_time_output);

    printf("%s (%s -> %s)\n", session_time_output, session_init_time_output,
           session_finished_time_output);
  }
  printf("\n");

  return 0;
}

/**
 * Returns session duration in secs
 */
static time_t session_duration(struct session *session, time_t *now) {
  return now == NULL ? time_diff_s(session->lock.created_at, now_in_millis())
                     : time_diff_s(session->lock.created_at, *now);
}
