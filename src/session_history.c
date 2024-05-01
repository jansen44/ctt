#include "session_history.h"

static void append_title(FILE *f);
static void format_history_item(struct history_item *item, char *dst);

void get_history_path(char *path, size_t max_path_size) {
  get_ctt_dir_path(path, max_path_size);
  strlcat(path, "/history", max_path_size);
}

int append_history_item(char *history_path, struct history_item *item) {
#define TRY_OPEN(mode)                                                         \
  f = fopen(history_path, mode);                                               \
  if (f == NULL) {                                                             \
    return errno;                                                              \
  }

  FILE *f = NULL;
  if (!check_file_exists(history_path)) {
    TRY_OPEN("a");
    append_title(f);
  } else {
    TRY_OPEN("a");
  }

  char history_line[MAX_HISTORY_LINE_SIZE] = {0};
  format_history_item(item, history_line);
  fprintf(f, "%s", history_line);
  fclose(f);

  return 0;
}

struct history get_history(char *history_path) {}

static void append_title(FILE *f) {
  fprintf(f, "DURATION(s),INITIALIZED_AT(ms),FINISHED_AT(ms)\n");
}

static void format_history_item(struct history_item *item, char *dst) {
  snprintf(dst, MAX_HISTORY_LINE_SIZE, "%ld,%ld,%ld\n", item->duration,
           item->initialized_at, item->finished_at);
}
