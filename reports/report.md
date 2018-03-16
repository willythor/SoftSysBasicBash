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

### Tab completion

Our shell supports tab auto-complete. This allows a user to enter the begining of a filename or folder and press tab and have the shell autocomplete with a probable filename/directory.

An example of this is as follows:

```
willAndDave@basicBash:~/home/willem/Documents/School/SoftSys/BasicBash$ ls
.
README.md
src
.git
Makefile
basicbash
obj
reviewable.js
include
reports
..
.gitignore

willAndDave@basicBash:~/home/willem/Documents/School/SoftSys/BasicBash$ cd s
```

At this point, if the user presses tab, the shell will autocomplete the command as follows:
```
willAndDave@basicBash:~/home/willem/Documents/School/SoftSys/BasicBash$ cd src
```
Since `src` is the only entry that begins with 's'.

### Learning Goals Evaluation

#### David

I would say I ended up solidly in the middle. I got waaaaay more comfortable with pointers, as I got to write functions that took in `**char`, and it wasn't terrifying. C sometimes blows my mind still, and it seems like incredibly simple things are really tough. I also realized I'm still a little fuzzy on how function arguments work (and how functions can actually modify arguments in a way that is visible to the caller, ie, taking an input string and pointing it at another string).

#### Will

My understanding of pointers has steadily increased throughout the course of this project. It is not quite at the **point** where I'd like it to be, but I'm definitely way better off than I was at the start of this project. As for understanding the inner workings of a terminal, I think I fell a little short. Instead of calling commands such as `ls` and `cd` we wrote our own commands, which I felt provided us with more learning opportunity, but less of an understanding of how the bash shell works. Lastly, my overall comfort with C has increased a tiny bit. I ran into a lot of trouble with header files, specifically depricated libraries and libraries that weren't cross-platform compatible. This was especially the case when it came to commands such as `getch()` -- a command that allows us to monitor user key-input as opposed to just a buffer from `stdin`. This helped grow my overall understanding of debugging and C libraries.