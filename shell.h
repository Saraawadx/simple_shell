#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

void _fork(char* buffer);
void shell();
char* _getline();
char* _strtok(char* input);
char *_print(char *argv);

#endif
