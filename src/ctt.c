#include "os.h"
#include <stdio.h>

int main() {
  if (initialize_ctt_dirs() != 0) {
    perror("ERR: Could not initialize dirs");
    return 1;
  }

  return 0;
}
