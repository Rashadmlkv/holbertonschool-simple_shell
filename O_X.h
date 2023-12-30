#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

extern char **environ;

char *read_command(void);
void parse_arguments(char *command, char **args);
int execute_command(char *command);
void search_and_execute(char *args[], char *command);
int main(void);

#endif#ifndef O_X_H
#define O_X_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void checkcommand(void);
int splitcommand(char *str, char *stri);
int hcp(void);
int creatprocs(char *arg[]);
int exec(char* arg[]);
#endif
