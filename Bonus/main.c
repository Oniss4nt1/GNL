#include <stdio.h>
#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please, enter the file names");
		return (1);
	}
	while (argc > 1)
	{
		int fd = open(argv[argc - 1], O_RDONLY);
		if (fd <= -1)
		{
			printf("Failed to open the file: %s\n", argv[argc - 1]);
			argc--;
		}
		else
		{
			char *line = get_next_line(fd);
			while (line != NULL)
			{
				printf("%s", line);
				free(line);
				line = get_next_line(fd);
			}
			close(fd);
			argc--;
		}
	}
	return (0);
}
