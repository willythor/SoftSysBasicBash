# BasicBash Terminal Emulator Project Update
## Will Thorbecke and David Abrahams

## Goal
Create a basic terminal like interface that allows a user to traverse their file structure using simple commands such as `cd` and `ls`, `pwd`, `mkdir`,
 
## Stretch Goal
Implement more advanced commands such as `grep`, `wc`, `sed`, `>`, `>>`, `command &`. Another stretch goal would have our commands work when files are large enough that we can’t fit the entire thing into RAM (or, in the case our RAM is incredibly limited)

## Learning Goals (Will)
- Become more fluent at C
- Understand the inner workings of a terminal
- Better understand pointers

## Learning Goals (David)
- Get better at C
- Become fluent with memory management in C (allocation, deallocation, and pointer magic)

## Things that were helpful

We both spent a ton of time working on stack overflow. We didn't really have any specific useful resources. One page that stood out (because we did a lot of string-parsing work) was:

https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c

The top 2 answers gave us code/syntax we used throughout the project.

## What we got done

### `cd` and `ls`

```
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
```

We implemented these two simple directory traversing functions.

### An awesome Makefile/build system

We wrote a [Makefile](../Makefile) which uses implicit rules to compile all our source code to `.o`, and then link them together. It doesn't look that impressive, but we both actually understand the file, and can use the principles behind it on any future C project, which is exciting.


### Cool chaining via recursion

Our shell supports "pipeing" or sorts between commands (sort of). The code that actually does this is a little spaghetti-like (we're not proud of this), but here's the high level idea:

* User inputs a string. We split the string on `|`.
* If the resulting split-string has one-substring, we do that one command (ie, `cd ..`).
* If there arer multiple substrings, we recursively process the substrings, and feed the output from each command to the next in sequence.

For example, if my directory structure looks like:

```
dir1
 |
 --->dir2
      |
      -->file1.txt
```

and the shell is in `dir1`, `ls` produces `dir2`. We can do `ls | cd`, which feeds `dir1` to `cd`, and moves us into `dir2`. (We realize this is not actually how `|` works, it was just one way to get some functionality working in the time we had for this project).

### Learning Goals Evaluation

#### David

I would say I ended up solidly in the middle. I got waaaaay more comfortable with pointers, as I got to write functions that took in `**char`, and it wasn't terrifying. C sometimes blows my mind still, and it seems like incredibly simple things are really tough. I also realized I'm still a little fuzzy on how function arguments work (and how functions can actually modify arguments in a way that is visible to the caller, ie, taking an input string and pointing it at another string).
