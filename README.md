# yshell
a simple shell written in one day in C, because why not

yshell provides a simple UNIX based POSIX based shell with minimal functionality

## features
- basic command tokenization using whitespace delimiters
- built in exit command for terminating the shell
- built in cd command for changing dirs
- execute external commands using execvp(), fork(), and waitpid()
- argument limit of 127 per command

## requirements
- POSIX compliant OS
- any C compiler

## compiling
```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -o yshell main.c
```

## scope
this was made as a small learning project in a single day, it doesn't aim or plan to implement full POSIX compliance and was only written in 118 lines of code
- arguments are separated by whitespace only.
- synchronous execution only
- no support for quoting or escaping arguments.
etc.

## license
[unlicense](LICENSE)
