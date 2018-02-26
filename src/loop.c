
#include <stdio.h>
#include <stdlib.h>
#include "../include/loop.h"
#include "../include/matcher.h"
#include "../include/input.h"
#include "../include/commands.h"

void loop() {
  char *input;
  while (matcher(input = readLine()) != QUIT) {
    printf("Your entered: %s\n", input);
    if (matcher(input) == LS) ls();
    if (matcher(input) == CD) cd("..");
  }
  printf("QUIT");
}
