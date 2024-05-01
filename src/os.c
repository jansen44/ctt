#include "os.h"

static int create_dir_if_not_exist(char *path);
static void ctt_dir_path(char *path, size_t max_path_size);

void ctt_lock_path(char *path, size_t max_path_size) {
  ctt_dir_path(path, max_path_size);
  strlcat(path, "/.lock", max_path_size);
}

int initialize_ctt_dirs() {
  int errno;

  char cfg_path[MAX_PATH_SIZE];
  ctt_dir_path(cfg_path, MAX_PATH_SIZE);

  errno = create_dir_if_not_exist(cfg_path);
  return errno;
}

static void ctt_dir_path(char *path, size_t max_path_size) {
  char *home = getenv("HOME");
  strlcat(path, home, max_path_size);
  strlcat(path, "/.local/share/ctt", max_path_size);
}

static int create_dir_if_not_exist(char *path) {
  struct stat st = {0};
  if (stat(path, &st) == -1) {
    return mkdir(path, 0700);
  }
  return 0;
}
