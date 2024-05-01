#ifndef _CTT_OS_
#define _CTT_OS_

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PATH_SIZE 255

char *ctt_cfg_path();
char *ctt_data_path();

int initialize_ctt_dirs();

#endif
