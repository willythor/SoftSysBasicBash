#include <stdlib.h>
#include <string.h>

#include "../include/matcher.h"


/**
 * @param p a pointer to a char*
 */
void double_string_size(char **p, int oldlen) {
  char *oldstring = *p;
  char *newstring = malloc(sizeof(char) * oldlen * 2);
  strcpy(newstring, oldstring);
  *p = newstring;
}

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
