#ifndef O_X_H
#define O_X_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int checkcommand(void);
int splitcommand(char *str, char *stri);
int hcp(void);
int creatprocs(char *arg[]);
int exec(char* arg[]);
#endif
