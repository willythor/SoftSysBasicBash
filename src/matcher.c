#include <string.h>
#include "../include/matcher.h"


int matcher(char *input) {
  if (strcmp(input, "quit") == 0) {
    return QUIT;
  }
  if (strncmp(input, "cd", 2) == 0) {
    return CD;
  }
  if (strncmp(input, "ls", 2) == 0) {
    return LS;
  }
  return 1;
}
