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

## What we’ve done so far…
We’ve implemented `cd` and `ls` commands alongside a script that constantly listens for and parses user input in order to execute said commands. These commands don’t execute the bash `ls` and `cd` commands but run our own C functions and print the results to `stdout`. Additionally, we have a non-trivial Makefile that takes care of compiling our project.
Alongside StackOverflow, these are the resources we’ve been using:
 
A tutorial on writing your own Bash shell: https://brennan.io/2015/01/16/write-a-shell-in-c/

Another tutorial: https://www.geeksforgeeks.org/making-linux-shell-c/
 
And this: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
 
We also furiously googled while making the makefile. There wasn’t any one resource we used for this. We knew what we wanted, and used a combination of make docs and stack overflow until we understand our build system, and were satisfied with it.

## Current Tasks 
1. Better matching for user input: We would like to be able to chain commands together, and to not have to adhere to specific syntax (ie, `ls` must be first two characters entered) in order for our shell to work. One our shell accepts variable amounts of whitespace, as well as chaining via pipes, this task will be done. (David)
2. Write a function that allows a user to click `tab` such that it completes their input to match a file or folder in their current directory. (Will)
3. Add the bash command `touch` that will let a user enter `touch <file_name>` in order to create a new file in the current directory with the given name. (Will)
