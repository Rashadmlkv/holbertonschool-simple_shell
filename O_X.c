#include "O_X.h"

/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;

int main(void)
{
	char *buff = NULL, *token = NULL;
	int size = 1, kiddo = 0, stat = 0;
	char *arg[] = {"" ,NULL};
	size_t len = 33;
	while (1)
	{
		size = getline(&buff, &len, stdin);
		if (size == -1)
		{
			free(buff);
			exit(0);
		}
		else if (buff == NULL)
			free(buff);
/*		else if (buff[size - 1] == '\n')
			buff[size - 1] = '\0';*/

		kiddo = fork();
		if (kiddo == -1)
			printf("Process error!\n");
		if (kiddo == 0)
		{
			token = strtok(buff, "\n");
			while (token != NULL)
			{
				token = strtok(NULL, "\n");
			}
			if (buff[0] != '/')
				return (0);
			execve(buff, arg, environ);
			return (0);
		}
		else
		{
			wait(&stat);
		}
	}
	return (0);
}
