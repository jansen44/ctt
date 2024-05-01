#ifndef _CTT_HISTORY_
#define _CTT_HISTORY_

#include "os.h"
#include "time.h"

#include <stdlib.h>
#include <sys/errno.h>

#define MAX_HISTORY_LINE_SIZE 100

#define ERR_HISTORY_FILE_NOT_FOUND 10

struct history_item {
  time_t initialized_at;
  time_t finished_at;
  time_t duration;
};

struct history {
  struct history_item *items;
  size_t history_len;
  size_t cap;
};

int get_history(char *history_path, struct history *history);
int append_history_item(char *history_path, struct history_item *item);
void get_history_path(char *path, size_t max_path_size);

#endif
