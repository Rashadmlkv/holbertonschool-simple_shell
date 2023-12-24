#include "O_X.h"

/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;

int isdash(char *str,char *argv[])
{
	if(str[0] == '/')
		execve(str, argv, environ);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char *buff = NULL, *token = NULL, *ext = "exit";
	int size = 1, kiddo = 0, stat = 0;
	char *arg[] = {"" ,NULL};
	size_t len = 33;

	if (ac == 1)
	{
		arg[0] = av[1];
	}
	else if (ac > 1)
	{
		int i, j = 2;

		arg[0] = av[1];
		for (i = 1; i < ac - 2)
		{
			arg[i] = av[j];
		}
	}

	while (1)
	{
		size = getline(&buff, &len, stdin);
		token = strtok(buff, " \n");
		if (size == -1 || *buff == *ext)
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
			if (buff[0] == '.')
			{
				hcp();
			        arg[0] = "./hbtn_ls";
				arg[1] = "/var";
				arg[2] = NULL;
				execve("./hbtn_ls", arg, environ);
			}
			else
			{
				token = strtok(buff, " \n");
				while (token != NULL)
				{
					isdash(token, arg);
					token = strtok(NULL, " \n");
				}
			}
		}
		else
		{
			wait(&stat);
		}
	}
	return (0);
}
