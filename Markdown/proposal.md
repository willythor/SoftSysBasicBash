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

## Resources
We plan on becoming more fluent in our use of everyday terminal commands using the UNIX tutorials posted on the SoftSys Google site.
This is a tutorial on writing your own Bash shell: https://brennan.io/2015/01/16/write-a-shell-in-c/

Another tutorial: https://www.geeksforgeeks.org/making-linux-shell-c/
 
And this: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

## Tasks
1. Write a script that receives user input and looks like a bash shell (David)
2. Write a script that parses user input for commands such as `ls` and `cd` (Will)
3. Write a function that prints out all the files in a certain directory (Will)
 
