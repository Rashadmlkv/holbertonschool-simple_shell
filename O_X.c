#include "O_X.h"

/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;

int isdash(char *str,char *arg[])
{
	if(str[0] == '/')
		execve(str, arg, environ);
	return (0);
}

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
			if (buff[0] == '.')
			{
				hcp();
				token = strtok(buff, " ");
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
