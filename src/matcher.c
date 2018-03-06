#include <stdlib.h>
#include <string.h>

#include "../include/matcher.h"


char* first_substring(char *s, char **tokens, int numtokens) {
  int slen = strlen(s); // doesn't include null-term
  char *substring = malloc(sizeof(char) * slen);
  for (int i = 0; i <= slen; i++) {
    for (int j = 0; j < numtokens; j++) {
      char *token = tokens[j];
      int tokenlen = strlen(token);
      if (strncmp(token, s + i, tokenlen) == 0) {
        substring[i] = '\0';
        return substring;
      }
    }
    substring[i] = s[i];
  }
  return substring;
}

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
