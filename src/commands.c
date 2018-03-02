#include <dirent.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/error.h"

char* concat(const char *s1, const char *s2) {
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}


void displayDirectoryName(int newLine) {
  char cwd[1024];

  if (newLine) {
    printf("%s\n",concat(concat("willAndDave@basicBash:~", getcwd(cwd, sizeof(cwd))),"$ "));
  }
  else {
    printf("%s",concat(concat("willAndDave@basicBash:~", getcwd(cwd, sizeof(cwd))),"$ "));
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
  char *curLoc = "./";
  if (loc == NULL){
  //  printf("%s\n","not enough arguements");
    return;
  }

  char *directory = concat(curLoc, loc);
  int success;
  
  success = chdir(directory);
  free(directory);
  return (success == 0) ? SUCCESS : FAILURE;
}


