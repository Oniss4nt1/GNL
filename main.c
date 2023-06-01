#include <stdio.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char *remaining_chr = NULL;
	int fd = open("arquivo.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open the file");
		return (1);
	}
	remaining_chr = get_next_line(fd);
	if (remaining_chr == NULL)
	{
		printf("An error occurred while reading files");
		return (1);
	}
	while (remaining_chr != NULL)
	{
		printf("Lines read: %s", remaining_chr);
		free(remaining_chr);
		remaining_chr = get_next_line(fd);
	}
	close(fd);
	return(0);
}