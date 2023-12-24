#include "O_X.h"
/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;

int exec(char *str,char *argv[])
{
	if(str[0] == '/')
		execve(str, argv, environ);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char *buff = NULL, *token = NULL, *ext = "exit", *temp;
	int size = 1, kiddo = 0, stat = 0, incr;
	char *arg[] = {"" ,NULL};
	size_t len = 33;
	(void)env;

	if (ac > 1)
	{
		buff = av[1];
		for (incr = 0; incr < ac; incr++)
		{
			arg[incr] = av[incr+1];
		}
		exec(buff,arg);
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
		else if (buff[size - 1] != 'n')
			buff[size + 1] = '\0';

		kiddo = fork();
		if (kiddo == -1)
			printf("Process error!\n");
		if (kiddo == 0)
		{
			if (buff[0] == '.')
			{
				hcp();
				for (incr = 0; incr < ac; incr++)
				{
					arg[incr] = av[incr+1];
				}

				execve(arg[0], arg, environ);
			}
			else
			{
				token = strtok(buff, " \n");
				while (token != NULL)
				{
					temp = token;
					token = strtok(NULL, " \n");
					arg[0] = temp;
					arg[1] = token;
					exec(temp, arg);
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
