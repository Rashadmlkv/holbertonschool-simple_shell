#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 1024

/**
 * copier - copy the content of first argument to another.
 *
 * @file_from: source file.
 *
 * @file_to: destination file.
 */

int copier(void)
{
	

	fd2 = open(file_from, O_RDONLY);
	if (fd2 == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		exit(98);
	}
	umask(0);
	fd = open(file_to, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	while (r > 0)
	{
		r = read(fd2, buf, BUFFER_SIZE);
		w = write(fd, buf, r);
		if (r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
			exit(98);
		}
		if (fd == -1 || w == -1)
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to), exit(99);
	}
	c = close(fd);
	if (c == -1)
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd), exit(100);
	free(buf);
	
	return (0);
}
