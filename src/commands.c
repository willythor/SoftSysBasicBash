#include <dirent.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/error.h"
#include "../include/matcher.h"
#include "../include/commands.h"

char* concat(const char *s1, const char *s2) {
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

char *ls(char *input) {
  DIR *d;
  struct dirent *dir;
  d = opendir(concat("./", input));
  char *s = "";

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strlen(s) == 0) s = dir->d_name;
      printf("%s\n", dir->d_name);
    }
    closedir(d);
    return s;
  }
  return s;
}


char *cd(char *loc) {
  if (loc == NULL) return "";

  char *curLoc = "./";
  char *directory = concat(curLoc, loc);
  int success;
  
  success = chdir(directory);
  free(directory);
  return (success == 0) ? "" : "";
}



char* process_command(char *command, char* prevCommandOutput) {
  // printf("hello");
  char *commands[1024];
  int numTokens = 1;
  char *tokens[1] = {"|"}; // TODO: implement more tokens
  int numCommands = getCommands(command, tokens, numTokens, commands);
  char *myoutput = malloc(sizeof(char) * (strlen(prevCommandOutput + 1)));
  strcpy(myoutput, prevCommandOutput);
  if (numCommands == 1) {
    char *singleCommand = commands[0];
    char *tokenized[1024];
    char *tokensplit[1] = {" "}; // for now, only split on spaces
    int numTokens = getCommands(singleCommand, tokensplit, 1, tokenized);
    char *command = malloc(sizeof(char) * (strlen(prevCommandOutput + 1)));
    strcpy(command, prevCommandOutput);
    if (strlen(command) == 0 && numTokens > 1) {
      command = tokenized[1];
    }
    if (matcher(tokenized[0]) == LS) {
      return ls(command);
    }
    if (matcher(tokenized[0]) == CD) {
      return cd(command);
    }
    return "quit";
  } else {
    for (int i = 0; i < numCommands; i++) {
      myoutput = process_command(commands[i], myoutput);
    }
    return myoutput;
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

