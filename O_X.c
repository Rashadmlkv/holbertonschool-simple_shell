#include "O_X.h"
/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;
int exec(char *str,char *arg[])
{
	if(str[0] == '/')
		execve(str, arg, environ);
	return(-1);
}
int main(int ac, char **av, char **env)
{
	char *buff = NULL, *token = NULL, *ext = "exit";
	int  size = 0, kiddo = 0, stat = 0, incr;
	char *arg[] = {"" ,NULL};
	size_t len = 33;
	(void)env;


        if (ac > 1) /* uninteractive mode */
	{
		buff = av[1];
		for (incr = 0; incr < ac; incr++)
		{
			arg[incr] = av[incr+1];
		}
		exec(buff,arg);
	}


	while (1)  /* interactive mode */
	{
		size = getline(&buff, &len, stdin);
		if (access(buff, F_OK) == -1 && *buff != *ext)
		{
			perror("Error:");
			exit(2);
		}
		if (size == -1 || *buff == *ext)
		{
			exit(0);
		}
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
				exec(arg[0], arg);
			}
			else
			{
				arg[0] = token;
				while (token != NULL)
				{
					token = strtok(NULL, " \n");
					arg[1] = token;
					arg[2] = NULL;
					exec(arg[0], arg);
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
