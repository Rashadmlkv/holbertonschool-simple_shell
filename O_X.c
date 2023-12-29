#include "O_X.h"
/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
extern char **environ;
void checkcommand(void) /* get and check commands */
{
	int size = 0;
	size_t len = 0;
	char *buff = NULL;
	char *ext = "exit", *env = "env";
	char **envi = environ;

	size = getline(&buff, &len, stdin);
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
			splitcommand(buff, " \n"); }
		else if (buff[0] == '/' || buff[0] == ' ') /* exec from dir */
		{
			splitcommand(buff, " \n"); }
	        else if (*buff == *env)
		{
			for (; *envi; envi++)
			{
				printf("%s\n", *envi);
			}
			free(*envi);
			free(buff);
		}
		else /* find and exec */
		{
			splitcommand(buff, ":"); }
	}
}

int splitcommand(char *str, char *stri)  /* split and put in array */
{
	int i;
	char *token = NULL, *token2 = NULL, *filename = NULL, *path = NULL;
	char abspath[128], cpypath[128];
	char *arg[] = {"" , NULL};

	token2 = strtok(str, " \n");
	filename = token2;
	for (i = 0; token2 != NULL; i++)
        {
		arg[i] = token2;
		token2 = strtok(NULL, " \n"); }
	arg[i] = NULL;

	if (strcmp(stri, ":") == 0)
	{
		path = getenv("PATH");
	        snprintf(cpypath, sizeof(cpypath), "%s", path);
		token = strtok(cpypath, stri);
		while (token != NULL)
		{
			snprintf(abspath, sizeof(abspath), "%s/%s", token, filename);
			arg[0] = abspath;
			if (access(arg[0], X_OK) == 0)
		        {
				creatprocs(arg);
				free(token2);
				free(filename);
				return (0); }
			token = strtok(NULL, stri);
		}
		fprintf(stderr, "./hsh: 1: %s: not found\n", filename);
		free(token);
		free(token2);
		free(filename);
		exit(127);
	}
	else
		creatprocs(arg);
	free(token);
	free(token2);
	return (0);
}
/* https://www.youtube.com/watch?v=k85mRPqvMbE */
int creatprocs(char *arg[])
{
	int status = 0, pid = 0;

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
	execve(arg[0], arg, environ);
	return (0);
}

int main(int ac, char **av)
{
	if (ac > 1)
	{
		if (av[1][0] == '\n')
			av[1][0] = ' ';
		av++;
		splitcommand(*av, " :\n");
	}
	else
	{
		while (1)
		{
			checkcommand();
		}
	}
	return (0);
}
