#include <dirent.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/error.h"
#include "../include/matcher.h"

char* concat(const char *s1, const char *s2) {
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}


void process_command(char *command) {
  char *commands[1024];
  int numTokens = 1;
  char *tokens[1] = {"|"}; // TODO: implement more tokens
  int numCommands = getCommands(command, tokens, numTokens, commands);
  if (numCommands == 1) {
    char *singleCommand = commands[0];
    char *tokenized[1024];
    char *tokensplit[1] = {" "}; // for now, only split on spaces
    int numTokens = getCommands(singleCommand, tokensplit, 1, tokenized);
    printf("%s", tokenized[0]);
  } else {
    for (int i = 0; i < numCommands; i++) {
      process_command(commands[i]);
    }
  }
}



void displayDirectoryName(int newLine) {
  char cwd[1024];

  if (newLine) {
    printf("%s%s%s\n","willAndDave@basicBash:~", getcwd(cwd, sizeof(cwd)),"$ ");
  }
  else {
    printf("%s%s%s","willAndDave@basicBash:~", getcwd(cwd, sizeof(cwd)),"$ ");
  }
}

int ls() {
  DIR *d;
  struct dirent *dir;
  d = opendir(".");

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
    return SUCCESS;
  }
  return FAILURE;
}


int cd(char *loc) {
  if (loc == NULL) return FAILURE;

  char *curLoc = "./";
  char *directory = concat(curLoc, loc);
  int success;
  
  success = chdir(directory);
  free(directory);
  return (success == 0) ? SUCCESS : FAILURE;
}


