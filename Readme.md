# miniSHELL

## This project is about
* parsing
* file descriptors
* *nix terminal commands

## Main part 
Own implementation shell.  
It handles:  
* pipes (|) and redirections (< > and >>)  
* environment variables and "$?" command  
* common shell commands like: cat, ls, grep, ps e.t.c  
* builtin commands: echo, cd, pwd, export, unset, env, exit  
* different commands in one line like : "cd .. ; ls -l; cat somefile.txt"
* ctrl-C and ctrl-D signals

## How to launch
1) run "make" in the root
2) execute ./minishell

![Alt text](mshl.gif)