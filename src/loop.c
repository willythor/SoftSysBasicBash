
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/loop.h"
#include "../include/matcher.h"
#include "../include/input.h"
#include "../include/commands.h"
#include "../include/error.h"

void loop() {
  char *input;
  displayDirectoryName(0);
  int success;
  while (matcher(input = readLine()) != QUIT) {
    success = SUCCESS;
    if (matcher(input) == LS) {
      if (ls() == FAILURE) {
        success = FAILURE;
      }
      displayDirectoryName(0);
    } else if (matcher(input) == CD) {
      strsep(&input," ");
      if (cd(strsep(&input," ")) == FAILURE) success = FAILURE;
      displayDirectoryName(0);
    } else if (matcher(input) != QUIT) success = FAILURE;

    // handle invalid input
    if (success == FAILURE) {
      printf("Invalid command: %s\n", input);
      displayDirectoryName(0);
    }
  }
  printf("QUIT");
}
