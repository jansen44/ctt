#include "os.h"

static int create_dir_if_not_exist(char *path);

char *ctt_cfg_path() {
  char *home = getenv("HOME");
  char *path = (char *)malloc(MAX_PATH_SIZE);
  strncat(path, home, MAX_PATH_SIZE);
  strncat(path, "/.local/share/ctt", MAX_PATH_SIZE);
  return path;
}

char *ctt_data_path() {
  char *path = ctt_cfg_path();
  strncat(path, "/data", MAX_PATH_SIZE);
  return path;
}

int initialize_ctt_dirs() {
  int errno;

  char *cfg_path = ctt_cfg_path();
  errno = create_dir_if_not_exist(cfg_path);
  free(cfg_path);
  if (errno != 0) {
    return errno;
  }

  char *data_path = ctt_data_path();
  errno = create_dir_if_not_exist(data_path);
  free(data_path);
  return errno;
}

static int create_dir_if_not_exist(char *path) {
  struct stat st = {0};
  if (stat(path, &st) == -1) {
    return mkdir(path, 0700);
  }
  return 0;
}
