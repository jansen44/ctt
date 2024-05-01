#include "lock.h"

static int init_lock(char *lock_path);
static int get_lock(char *lock_path, struct lock *lock);

lockresp_t get_or_create_lock(struct lock *lock) {
  char lock_path[MAX_PATH_SIZE] = {0};
  ctt_lock_path(lock_path, MAX_PATH_SIZE);

  int output = get_lock(lock_path, lock);
  if (output == 0) {
    return LOCK_RETRIEVED;
  }

  if (init_lock(lock_path) != 0) {
    return ERR_CREATING_LOCK;
  }
  return LOCK_CREATED;
}

static int init_lock(char *lock_path) {
  FILE *f = fopen(lock_path, "w+x");
  if (f == NULL) {
    return errno;
  }
  return 0;
}

static int get_lock(char *lock_path, struct lock *lock) {
  struct stat st;
  if (stat(lock_path, &st) == -1) {
    return 1;
  }

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
  struct timespec spec = st.st_birthtimespec;
  time_t time = time_in_millis(&spec);
#else
  time_t time = st.st_mtime;
#endif

  lock->created_at = time;
  return 0;
}
