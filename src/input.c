#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "../include/input.h"
#include "../include/commands.h"

char *readLine() {
  int lineCapacity = 64;
  int lineSize = 0;
  char *line = malloc(sizeof(char) * lineCapacity);
  char c;
  //Loop until c is EOF or a newline char

  while ((c = getchar()) != EOF && c != '\n') {
    lineSize++;
    // Need to leave one char on the end for the terminator
    if (lineSize == lineCapacity) {
      lineCapacity *= 2;
      line = realloc(line, sizeof(char) * lineCapacity);
    }
    line[lineSize - 1] = c;
  }
  line[lineSize] = '\0';
  return line;
}

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

char *readLineTab() {
  int lineCapacity = 64;
  int lineSize = 0;
  char *line = malloc(sizeof(char) * lineCapacity);
  char c;
  char e;

  c = getch();

  while (c != '\n') {
    if (c == '\t') {
      char *newLine = tabComplete(line);
      printf("%s", newLine);
    }
    //apparently this is the way to check for a backspace, not '\b'
    else if (c == 0x7f) {
      if (lineSize > 0) {
        lineSize--;
        printf("\b");
      }
    }
    else {
      lineSize++;
      //need to print out current char because I'm not echoing
      printf("%c",c);
      // Need to leave one char on the end for the terminator
      if (lineSize == lineCapacity) {
       lineCapacity *= 2;
       line = realloc(line, sizeof(char) * lineCapacity);
      }
      line[lineSize - 1] = c;
    }
    c = getch();
  }

  printf("%c",'\n');

  line[lineSize] = '\0';
  return line;
}
