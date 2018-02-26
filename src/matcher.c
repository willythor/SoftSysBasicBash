#include <string.h>
#include "../include/matcher.h"


int matcher(char *input) {
  if (strcmp(input, "quit") == 0) {
    return quit;
  }
  if (strncmp(input, "cd", 2) == 0) {
    return cd;
  }
  if (strncmp(input, "ls", 2) == 0) {
    return ls;
  }
  return 1;
}
