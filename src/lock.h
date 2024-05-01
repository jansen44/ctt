#ifndef _CTT_LOCK_
#define _CTT_LOCK_

#include "os.h"
#include "time.h"

#include <stdio.h>
#include <sys/errno.h>

#define ERR_CREATING_LOCK -1
#define LOCK_RETRIEVED 0
#define LOCK_CREATED 1

typedef int lockresp_t;

struct lock {
  time_t created_at;
};

lockresp_t get_or_create_lock(struct lock *lock);

#endif
