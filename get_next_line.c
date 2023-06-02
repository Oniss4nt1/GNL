/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:18:24 by brunrodr          #+#    #+#             */
/*   Updated: 2023/06/01 18:22:03 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
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

	if (str == NULL)
		return (NULL);
	p = str;
	while (*p && *p != '\n')
	{
		if (*p == '\n')
			p++;
		p++;
	}
	line = (char *)malloc(sizeof(char) * (p - str + 1));
	if (line == NULL)
		return (NULL);

	p = str;
	while (*p != '\n' && *p != '\0')
		*line++ = *p++;
	if (*p == '\n')
		*line++ = *p++;
	*line = '\0';
	return (line - (p - str));
}

static char	*get_remaining(char *str)
{
	char	*p;
	char	*remaining;
	char	*dest;

	p = str;
	while (*p != '\n' && *p)
		p++;
	if (*p == '\n' && *(p + 1) == '\0')
	{
		free(str);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(p) + 1));
	if (!remaining)
		return (NULL);
	dest = remaining;
	p++;
	while (*p != '\0')
		*dest++ = *p++;
	*dest = '\0';
	free(str);
	return (remaining - (p - str));
}

char	*read_lines(int fd, char *current_line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
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

char	*get_next_line(int fd)
{
	static char	*line;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);

	line = read_lines(fd, line);
	if (!(ft_strlen(line)))
	{
		free(line);
		return (NULL);
	}

	current_line = get_line(line);
	if (!current_line)
		return (NULL);

	line = get_remaining(line);
	return (current_line);
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