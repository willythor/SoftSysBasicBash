
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
  displayDirectoryName(0);
  while (strcmp(process_command(readLine(), ""), "quit") != 0) {
    printf("\n");
    displayDirectoryName(0);
  }
}
