#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "../include/input.h"
#include "../include/commands.h"
#include "../include/termios.h"

char *readLine() {
  int lineCapacity = 1000;
  int lineSize = 0;
  char *line = malloc(sizeof(char) * lineCapacity);
  char c;

  c = getch();

  while (c != '\n') {
    if (c == '\t') {
      char *newLine = tabComplete(line);
      for (int i = 0; i < lineSize; i++) {
        printf("\b \b");
      }
      line = newLine;
      lineSize = strlen(line);
      printf("%s", line);
    }
    //0x7f checks for a backspace
    else if (c == 0x7f) {
      if (lineSize > 0) {
        lineSize--;
        //deletes the previously inputted character
        printf("\b \b");
      }
    }
    else {
      //need to print out current char because I'm not echoing
      printf("%c",c);
      // Need to leave one char on the end for the terminator
      if (lineSize == lineCapacity) {
       lineCapacity *= 2;
       line = realloc(line, sizeof(char) * lineCapacity);
      }
      line[lineSize] = c;
      lineSize++;
    }
    c = getch();
  }
  
  printf("%c",'\n');
  line[lineSize] = '\0';
  return line;
}
