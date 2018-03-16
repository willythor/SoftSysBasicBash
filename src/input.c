#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/input.h"

char *readLine() {
  int lineCapacity = 64;
  int lineSize = 0;
  char *line = malloc(sizeof(char) * lineCapacity);
  char c;
  // Loop until c is EOF or a newline char
  while ((c = getchar()) != EOF && c != '\n') {
    // Need to leave one char on the end for the terminator
    if (lineSize == lineCapacity) {
      lineCapacity *= 2;
      line = realloc(line, sizeof(char) * lineCapacity);
    }
    line[lineSize] = c;
    lineSize++;
  }
  line[lineSize] = '\0';
  return line;
}
