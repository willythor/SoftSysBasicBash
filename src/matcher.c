#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

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

// return true if substring matches token at the end
bool substring_match_on_end(char *substring, char *token) {
  int l1 = strlen(substring);
  int l2 = strlen(token);
  if (l1 < l2) return false;
  if (strncmp(substring + l1 - l2, token, l2 ) == 0) {
    return true;
  }
  return false;
}


/**
 * userInput: string, ie: "cat myfile.txt"
 * tokens: stuff to split on, ie: "|", "&&", etc
 * numtokens: len(tokens)
 * commands: 2d array to store split up commands in
 * returns: number of commands found in userInput
 */
int getCommands(
    char *userInput,
    char **tokens,
    int numtokens,
    char **commands
    ) {
  int substringStart = 0;
  int numCommands = 0;
  int slen = strlen(userInput); // doesn't include null-term
  char *substring = malloc(sizeof(char) * slen + 1); // +1 for the null-term
  for (int i = 0; i < slen; i++) {
    substring[i - substringStart] = userInput[i];
    for (int j = 0; j < numtokens; j++) {
      char *token = tokens[j];
      if (substring_match_on_end(substring, token)) {
        substring[i - substringStart - strlen(token) + 1] = '\0';
        commands[numCommands++] = substring;
        substring = malloc(sizeof(char) * slen + 1);
        substringStart = i + 1;
      }
    }
  }
  substring[slen - substringStart] = '\0';
  commands[numCommands++] = substring;
  return numCommands;
}
