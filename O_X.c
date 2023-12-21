#include "O_X.h"

/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
int main(void)
{
	char *buff;
	int size = 1, kiddo = 0, stat = 0;
	size_t len = 0;
	char *arg[] = {NULL};

	printf("::(O_X) SHELL::\n\t^d to exit\n");
	while (1)
	{
		printf("(O_X)");
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
			execve(buff, arg, NULL);
			printf("No such file or directory\n");
			return (0);
		}
		else
		{
			wait(&stat);
		}
	}
	return (0);
}
