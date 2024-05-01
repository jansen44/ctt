#include "os.h"

static int create_dir_if_not_exist(char *path);

int initialize_ctt_dirs() {
  int errno;

  char cfg_path[MAX_PATH_SIZE] = {0};
  get_ctt_dir_path(cfg_path, MAX_PATH_SIZE);

  errno = create_dir_if_not_exist(cfg_path);
  return errno;
}

void get_ctt_dir_path(char *path, size_t max_path_size) {
  char *home = getenv("HOME");
  strlcat(path, home, max_path_size);
  strlcat(path, "/.local/share/ctt", max_path_size);
}

int check_file_exists(char *path) {
  struct stat st = {0};
  return stat(path, &st) != -1;
}

static int create_dir_if_not_exist(char *path) {
  if (!check_file_exists(path)) {
    return mkdir(path, 0700);
  }
  return 0;
}
