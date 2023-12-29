#include "O_X.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int exec(char *str, char *arg[]) {
    if (str[0] == '/') {
        execve(str, arg, environ);
        perror("execve");
        return -1;
    } else {
        char *path = getenv("PATH");
        char *token;

        if (path == NULL) {
            fprintf(stderr, "./hsh: 1: %s: not found\n", arg[0]);
            free(path);
            exit(127);
        }

        token = strtok(path, ":");
        while (token != NULL) {
            char executable_path[256];
            snprintf(executable_path, sizeof(executable_path), "%s/%s", token, arg[0]);

            if (access(executable_path, X_OK) == 0) {
                if (execve(executable_path, arg, environ) == -1) {
                    perror("execve");
                    free(path);
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, ":");
        }
        free(path);
    }
    return 0;
}

void hcp() {
   
}

int main(int ac, char **av) {
    char *buff = NULL, *token = NULL;
    int size = 0, kiddo = 0, stat = 0;
    char *arg[3]; 
    size_t len = 33;

    if (ac > 1) {
        buff = av[1];
        arg[0] = buff;
        arg[1] = NULL;
        exec(buff, arg);
    }

    while (1) {
        printf(":) ");
        size = getline(&buff, &len, stdin);

        if (size == -1 || strncmp(buff, "exit", 4) == 0) {
            free(buff);
            exit(0);
        }

        token = strtok(buff, " \n");

        kiddo = fork();
        if (kiddo == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (kiddo == 0) {
            if (strncmp(buff, ".", 1) == 0) {
                hcp();
                arg[0] = "./hbtn_ls";
                arg[1] = "/var";
                arg[2] = NULL;
                exec(arg[0], arg);
            } else {
                arg[0] = token;
                arg[1] = NULL;

                while (token != NULL) {
                    token = strtok(NULL, " \n");
                    if (token != NULL) {
                        arg[1] = token;
                        arg[2] = NULL;
                        exec(arg[0], arg);
                    }
                }
            }
        } else {
            wait(&stat);
        }
    }

    return 0;
}
