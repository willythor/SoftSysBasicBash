
#include <stdio.h>
#include <stdlib.h>
#include "../include/loop.h"
#include "../include/matcher.h"
#include "../include/input.h"
#include "../include/commands.h"
#include <string.h>
#include <unistd.h>

#include "../include/error.h"

void loop() {
  char *input;
  int success = SUCCESS;
  displayDirectoryName(0);
   
  while (matcher(input = readLine()) != QUIT) {
    
    if (matcher(input) == LS) {
      if (ls() == FAILURE) success = FAILURE;
      displayDirectoryName(0);
    } else if (matcher(input) == CD) {
      if (cd("..") == FAILURE) success = FAILURE;
      displayDirectoryName(0);
    } else if (matcher(input) != QUIT) success = FAILURE;

    // handle invalid input
    if (success == FAILURE) {
      printf("Invalid command: %s\n", input);
    }
  }
  printf("QUIT");
}
