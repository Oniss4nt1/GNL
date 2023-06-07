#include <stdio.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//int main(int argc, char *argv[])
//{
//	if (argc < 2)
//	{
//		printf("Please, enter the name file");
//		return (1);
//	}
//
//	int fd = open(argv[1], O_RDONLY);
//	if (fd <= -1)
//	{
//		printf("Failed to open the file");
//		return (1);
//	}
//	
//	char *line = get_next_line(fd);
//	while (line != NULL)
//	{
//		printf("%s", line);
//		free(line);
//		line = get_next_line(fd);
//	}
//	close(fd);
//	return (0);
//}

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

//int main(int argc, char *argv[])
//{
//	if (argc < 2)
//	{//
//		printf("Please, enter the file names\n");
//		return 1;
//	}
//
//	for (int i = 1; i < argc; i++)
//	{
//		int fd = open(argv[i], O_RDONLY);
//		if (fd <= -1)
//		{
//			printf("Failed to open the file: %s\n", argv[i]);
//			continue;
//		}
//
//		char *line = get_next_line(fd);
//		while (line != NULL)
//		{
//			printf("%s\n", line);
//			free(line);
//			line = get_next_line(fd);
//		}
//
//		close(fd);
//	}
//
//	return 0;
//}