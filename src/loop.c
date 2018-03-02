
#include <stdio.h>
#include <stdlib.h>
#include "../include/loop.h"
#include "../include/matcher.h"
#include "../include/input.h"
#include "../include/commands.h"
#include <string.h>
#include <unistd.h>

void loop() {
  char *input;
  
  displayDirectoryName(0);

  while (matcher(input = readLine()) != QUIT) {
    if (matcher(input) == LS) {
      ls();
      displayDirectoryName(0);
    }
    if (matcher(input) == CD) {
      strsep(&input," ");
      cd(strsep(&input," "));
      displayDirectoryName(0);
    }
  }
  printf("QUIT");
}
