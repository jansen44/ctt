#ifndef _CTT_LOCK_
#define _CTT_LOCK_

#include "os.h"
#include "time.h"

#include <stdio.h>
#include <sys/errno.h>

struct lock {
  time_t created_at;
};

int init_lock(char *lock_path);
int get_lock(char *lock_path, struct lock *lock);
void get_lock_path(char *path, size_t max_path_size);

#endif
