#ifndef _CTT_OS_
#define _CTT_OS_

#include "time.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PATH_SIZE 255

void ctt_lock_path(char *path, size_t max_path_size);

int initialize_ctt_dirs();

#endif
