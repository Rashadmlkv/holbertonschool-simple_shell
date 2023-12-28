#include "O_X.h"
/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;
int checkcommand(void) /* get and check commands */
{
	int size = 0;
	size_t len = 0;
	char *buff = NULL;
	char *ext = "exit";

	size = getline(&buff, &len, stdin);
	printf("getline\n");
	if (size == -1 || buff == ext)
	{
		free (buff);
		exit(0);
	}
	else
	{
		if (buff[0] == '.')  /* copy and exec */
		{
			hcp();
			splitcommand(buff, " \n");
		}
		else if (buff[0] == '/') /* exec from dir */
		{
			splitcommand(buff, " \n");
		}
		else /* find and exec */
		{
			splitcommand(buff, ":");
		}
	}
}

int splitcommand(char *str, char *stri)  /* split and put in array */
{
	int i;
	char *token = NULL, *path = NULL, *filename = NULL, *token2 = NULL;
	char *arg[] = {"" , NULL};

	printf("strtok\n");
	token2 = strtok(str, " \n");
	filename = token2;
	if (strcmp(stri, ":") != 0)
	{
		printf("ss\n");
		for (i = 0; token2 != NULL; i++)
		{
			printf("Girmemeli\n");
			arg[i] = token2;
			token2 = strtok(NULL, stri);
		}
		arg[i] = NULL;
		creatprocs(arg);
		return (0);
	}



	path = getenv("PATH");
	for (i = 1; token2 != NULL; i++)
	{
		arg[i] = token2;
		token2 = strtok(str, " \n");
	}
	token = strtok(path, stri);
        arg[0] = strcat(token, filename);

	while (token != NULL)
	{
		if (access(arg[0], X_OK) != -1)
			creatprocs(arg);
		token = strtok(NULL, stri);
		arg[0] = strcat(token, filename);
	}
}

int creatprocs(char *arg[])
{
	int status = 0, pid = 0;

	printf("pid\n");
	pid = fork();

	if (pid == -1)
		perror("Process error");
	else if (pid == 0)
		exec(arg);
	else
		wait(&status);
	return (0);
}

int exec(char* arg[])
{
	printf("exec\n");
	execve(arg[0], arg, environ);
	return (-1);
}

int main(int ac, char **av, char **env)
{
	/* uninteractive mode */
	if (ac > 1)
	{
		;
	}

	/* interactive mode */
	while (1)
	{
		checkcommand();
	}
	return (0);
}
