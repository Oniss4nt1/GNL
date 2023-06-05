/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:05:00 by brunrodr          #+#    #+#             */
/*   Updated: 2023/06/05 14:16:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	find_breakline(char *str)
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

static char	*get_line(char *str)
{
	char	*p;
	char	*line;
	char	*dest;

	p = str;
	while (*p != '\n' && *p != '\0')
		p++;
	if (*p == '\n')
		p++;
	line = (char *)malloc(sizeof(char) * (p - str) + 1);
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
	char	*save_position;

	p = str;
	save_position = str;
	while (*p != '\n' && *p != '\0')
		p++;
	if (*p == '\n' && *(p + 1) == '\0')
	{
		free(str);
		return (NULL);
	}
	str = p;
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!remaining)
		return (NULL);
	p = remaining;
	while (*str != '\0')
		*p++ = *str++;
	*p = '\0';
	free(save_position);
	return (remaining);
}


char	*read_lines(int fd, char *current_line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes <= 0)
	{
		free(buffer);
		return (current_line);
	}
	buffer[read_bytes] = '\0';
	current_line = ft_strjoin(current_line, buffer);
	free(buffer);
	if (find_breakline(current_line))
		return (current_line);
	return (read_lines(fd, current_line));
}


char *get_next_line(int fd)
{
	static char *line[4096];
	char *current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return NULL;
	line[fd] = read_lines(fd, line[fd]);
	if (!ft_strlen(line[fd]))
		return NULL;
	current_line = get_line(line[fd]);
	if (!current_line)
		return NULL;
	line[fd] = get_remaining(line[fd]);
	return (current_line);
}
