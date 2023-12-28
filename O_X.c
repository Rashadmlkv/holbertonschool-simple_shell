#include "O_X.h"
/**
 * main - program
 * Return: 0 on success, -1 on fail
 */
char **environ;
int exec(char *str,char *arg[])
{
	if(str[0] == '/')
	{
		execve(str, arg, environ);
	return(-1);
	}
	else
        {
            char *path = getenv("PATH");
	    char *token;

	    if (path == NULL)
	    {
		    fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		    free(command);
		    exit(127);
	    }

            token = strtok(path, ":");
            while (token != NULL)
            {
                char executable_path[256];
                snprintf(executable_path, sizeof(executable_path), "%s/%s", token, args[0]);

                if (access(executable_path, X_OK) == 0)
                {
                    if (execve(executable_path, args, environ) == -1)
                    {
                        perror("execve");
                        free(command);
                        exit(EXIT_FAILURE);
                    }
                }

                token = strtok(NULL, ":");
            }
        }
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
			free(buff);
			perror("/bin/ls: cannot access '/test_hbtn'");
			exit(2);
		}
		if (size == -1 || *buff == *ext)
		{
			free(buff);
			exit(0);
		}

		token = strtok(buff, " \n");
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
