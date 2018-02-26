#include <dirent.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char* concat(const char *s1, const char *s2) {
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}


void ls() {
  DIR *d;
  struct dirent *dir;
  d = opendir(".");

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
}


void cd(char *loc) {
  char *curLoc = "./";
  char *directory = concat(curLoc, loc);
  int ret;
  
  ret = chdir(directory);
  printf("%d", ret);
}


int main(void) {
  char *newLoc = "..";
  cd(newLoc);
  ls();
  return(0);
}
