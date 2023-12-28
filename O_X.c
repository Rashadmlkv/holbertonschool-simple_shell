#include "O_X.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * exec - execute the command using execvp
 * @str: command path or name
 * @arg: arguments for the command
 * Return: -1 on failure, not reached on success
 */
int exec(char *str, char *arg[])
{
    if (str[0] == '/')
    {
        execve(str, arg, environ);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        char *path = getenv("PATH");
        char *token;

        if (path == NULL)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", arg[0]);
            exit(EXIT_FAILURE);
        }

        token = strtok(path, ":");
        while (token != NULL)
        {
            char executable_path[256];
            snprintf(executable_path, sizeof(executable_path), "%s/%s", token, arg[0]);

            if (access(executable_path, X_OK) == 0)
            {
                execve(executable_path, arg, environ);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, ":");
        }
    }
    return -1; // This line is not reached
}

int main(int ac, char **av, char **env)
{
    char *buff = NULL, *token = NULL, *ext = "exit";
    size_t len = 33;
    (void)env;

    if (ac > 1) /* uninteractive mode */
    {
        exec(av[1], av + 1);
    }

    while (1)  /* interactive mode */
    {
        ssize_t size = getline(&buff, &len, stdin);

        if (size == -1 || *buff == *ext)
        {
            free(buff);
            exit(0);
        }

        token = strtok(buff, " \n");

        if (buff[0] == '.')
        {
            hcp();
            exec("./hbtn_ls", (char *[]){"./hbtn_ls", "/var", NULL});
        }
        else
        {
            exec(token, (char *[]){token, NULL});
        }
    }

    return 0;
}
