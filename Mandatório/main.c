#include <stdio.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please, enter the name file");
		return (1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd <= -1)
	{
		printf("Failed to open the file");
		return (1);
	}
	
	char *line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

