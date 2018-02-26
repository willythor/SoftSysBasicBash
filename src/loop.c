
#include <stdio.h>
#include <stdlib.h>
#include "../include/loop.h"
#include "../include/matcher.h"
#include "../include/input.h"

void loop() {
  char *input;
  while (matcher(input = readLine()) != quit) {
    printf("Your entered: %s", input);
  }
  printf("QUIT");
}
