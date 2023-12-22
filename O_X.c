#include "O_X.h"

/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
int main(int ac, char **av, char **env)
{
	char *buff;
	int size = 1, kiddo = 0, stat = 0;
	char *arg[] = {NULL};
	size_t len = 0;
	(void)ac;
	(void)av;
	(void)*env;
	while (1)
	{
		size = getline(&buff, &len, stdin);
		if (size == -1)
			exit(0);
		else if (buff == NULL)
			free(buff);
		else if (buff[size - 1] == '\n')
			buff[size - 1] = '\0';


		kiddo = fork();
		if (kiddo == -1)
			printf("Process error!\n");
		if (kiddo == 0)
		{
			execve(buff, arg, env);
			return (0);
		}
		else
		{
			wait(&stat);
		}
	}
	return (0);
}
