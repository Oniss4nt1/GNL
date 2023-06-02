/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:18:24 by brunrodr          #+#    #+#             */
/*   Updated: 2023/06/02 18:36:23 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	lenght;

// 	lenght = 0;
// 	while (*s != '\0')
// 	{
// 		lenght++;
// 		s++;
// 	}
// 	return (lenght);
// }

// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*str;
// 	char	*p;

// 	if (s1 == NULL)
// 		s1 = "";
// 	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	p = str;
// 	while (*s1)
// 		*p++ = *s1++;
// 	while (*s2)
// 		*p++ = *s2++;
// 	*p = '\0';
// 	return (str);
// }

char	find_breakline(char *str)
{
	char	*p;

	p = str;
	if (str == NULL)
		return (0);
	while (*p != '\0')
	{
		if (*p == '\n')
			return (1);
		p++;
	}
	return (0);
}


char	*get_line(char *str)
{
	char	*p;
	char	*line;
	char	*dest;

	p = str;
	while (*p != '\n' && *p != '\0')
		p++;
	line = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!line)
		return (NULL);
	dest = line;
	while (*str != '\n' && *str != '\0')
		*dest++ = *str++;
	if (*str == '\n')
		*dest++ = *str++;
	*dest = '\0';
	return (line);
}

static char	*get_remaining(char *str)
{
	char	*p;
	char	*remaining;

	p = str;
	while (*p != '\n' && *p != '\0')
		p++;
	if (*p == '\0')
	{
		free(str);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * ft_strlen(p) + 1);
	if (!remaining)
		return (NULL);
	p = remaining;
	while (*str != '\n' && *str != '\0')
		str++;
	if (*str == '\n')
		str++;
	while (*str != '\0')
		*p++ = *str++;
	*p = '\0';
	return (remaining);
}

char	*read_lines(int fd, char *current_line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!find_breakline(current_line))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		current_line = ft_strjoin(current_line, buffer);
		if (!current_line)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (current_line);
}

char *get_next_line(int fd)
{
	static char line[BUFFER_SIZE + 1];
	char *current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return NULL;

	line[0] = '\0';

	line = read_lines(fd, line);
	if (!ft_strlen(line))
		return NULL;

	current_line = get_line(line);
	if (!current_line)
		return NULL;

	line = get_remaining(line);
	return current_line;
}


// int main(void)
// {
// 	char *remaining_chr = NULL;
// 	int fd = open("arquivo.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		printf("Failed to open the file");
// 		return (1);
// 	}
// 	remaining_chr = read_lines(fd, remaining_chr);
// 	if (remaining_chr == NULL)
// 	{
// 		printf("An error occurred while reading files");
// 		return (1);
// 	}
// 	printf("Lines read: %s", remaining_chr);
// 	close(fd);
// 	return(0);
// }