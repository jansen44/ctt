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

int get_history(char *history_path, struct history *history) {
  if (!check_file_exists(history_path)) {
    return ERR_HISTORY_FILE_NOT_FOUND;
  }

#define HISTORY_ITEM_CHUNK_SIZE 10
#define MAX_NUMBER_DIGITS 14

  history->items = (struct history_item *)malloc(sizeof(struct history_item) *
                                                 HISTORY_ITEM_CHUNK_SIZE);
  history->cap = HISTORY_ITEM_CHUNK_SIZE;

  FILE *f = fopen(history_path, "r");
  char line[MAX_HISTORY_LINE_SIZE] = {0};
  fgets(line, MAX_HISTORY_LINE_SIZE, f); // Ignore headers

  int i = 0;
  while (fgets(line, MAX_HISTORY_LINE_SIZE, f)) {
    int j = 0;

    char duration_str[MAX_NUMBER_DIGITS] = {0};
    int k = 0;
    while (line[j] != ',') {
      duration_str[k++] = line[j++];
    }
    duration_str[k] = '\0';
    j++;

    char initialized_at_str[MAX_NUMBER_DIGITS] = {0};
    k = 0;
    while (line[j] != ',') {
      initialized_at_str[k++] = line[j++];
    }
    initialized_at_str[k] = '\0';
    j++;

    char finished_at_str[MAX_NUMBER_DIGITS] = {0};
    k = 0;
    while (line[j] != '\n') {
      finished_at_str[k++] = line[j++];
    }
    finished_at_str[k] = '\0';

    time_t duration = strtol(duration_str, NULL, 10);
    time_t initialized_at = strtol(initialized_at_str, NULL, 10);
    time_t finished_at = strtol(finished_at_str, NULL, 10);

    struct history_item history_item = {
        .duration = duration,
        .initialized_at = initialized_at,
        .finished_at = finished_at,
    };
    history->items[i] = history_item;
    history->history_len = ++i;

    if (history->history_len + 1 == history->cap) {
      history->cap = history->cap + HISTORY_ITEM_CHUNK_SIZE;
      history->items =
          (struct history_item *)realloc(history->items, history->cap);
    }
  }

  int err = ferror(f);
  fclose(f);
  return err;
}

static void append_title(FILE *f) {
  fprintf(f, "DURATION(s),INITIALIZED_AT(ms),FINISHED_AT(ms)\n");
}

static void format_history_item(struct history_item *item, char *dst) {
  snprintf(dst, MAX_HISTORY_LINE_SIZE, "%ld,%ld,%ld\n", item->duration,
           item->initialized_at, item->finished_at);
}
