#ifndef _CTT_HISTORY_
#define _CTT_HISTORY_

#include "os.h"

#include <sys/errno.h>

#define MAX_HISTORY_LINE_SIZE 100

struct history_item {
  time_t initialized_at;
  time_t finished_at;
  time_t duration;
};

struct history {
  struct history_item *history;
};

struct history get_history(char *history_path);
int append_history_item(char *history_path, struct history_item *item);
void get_history_path(char *path, size_t max_path_size);

#endif
