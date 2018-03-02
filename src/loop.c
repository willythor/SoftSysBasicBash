
#include <stdio.h>
#include <stdlib.h>
#include "../include/loop.h"
#include "../include/matcher.h"
#include "../include/input.h"
#include "../include/commands.h"

#include "../include/error.h"

void loop() {
  char *input;
  int success = SUCCESS;
  while (matcher(input = readLine()) != QUIT) {
    if (matcher(input) == LS) {
      if (ls() == FAILURE) success = FAILURE;
    } else if (matcher(input) == CD) {
      if (cd("..") == FAILURE) success = FAILURE;
    } else if (matcher(input) != QUIT) success = FAILURE;

    // handle invalid input
    if (success == FAILURE) {
      printf("Invalid command: %s\n", input);
    }
  }
  printf("QUIT");
}
