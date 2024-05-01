#include "session_lock.h"
#include <stdio.h>

void get_lock_path(char *path, size_t max_path_size) {
  get_ctt_dir_path(path, max_path_size);
  strlcat(path, "/.lock", max_path_size);
}

int init_lock(char *lock_path) {
  FILE *f = fopen(lock_path, "w+x");
  if (f == NULL) {
    return errno;
  }
  return 0;
}

int get_lock(char *lock_path, struct lock *lock) {
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
