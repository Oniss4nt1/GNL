/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:18:24 by brunrodr          #+#    #+#             */
/*   Updated: 2023/06/07 11:21:22 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
** Get_next_line is a function that reads a file line by line.
** It returns a line ending with a newline, without the newline or NULL
*/

#include "get_next_line.h"

char		*read_lines(int fd, char *current_line);
static char	find_breakline(char *str);
static char	*get_line(char *str);
static char	*get_remaining(char *str);

/*
** This function checks if the fd is valid and if the BUFFER_SIZE is valid.
** If the fd is invalid or the BUFFER_SIZE is invalid, it returns NULL.
** If the fd is valid and the BUFFER_SIZE is valid, it calls the function read_lines.
** After read_lines, it checks if the line is empty. If it is empty, it returns NULL.
** If the line is not empty, it calls the function get_line.
** After get_line, it calls the function get_remaining.
*/

char	*get_next_line(int fd)
{
	static char	*line;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);
	line = read_lines(fd, line);
	if (!ft_strlen(line))
		return (NULL);
	current_line = get_line(line);
	if (!current_line)
		return (NULL);
	line = get_remaining(line);
	return (current_line);
}

/*
** This is a recursive function that reads the file line by line  
** according to the BUFFER_SIZE and allocates memory for the buffers. 
** It uses the function ft_strjoin to join two memory blocks.
** One of the mallocs is the buffer, which is the buffer that will be read.
** The other malloc is the current_line, which is the line that will be returned.
** The recursive function ends when it finds a breakline or when it reaches the end of the file.
*/

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

/*
** This function checks if the string has a breakline.
** If it has a breakline, it returns 1.
** If it doesn't have a breakline, it returns 0.
*/

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

/*
** This function checks if the string has a breakline.
** If it has a breakline, it allocates memory for the line
** and copies the string until the breakline.
*/

static char	*get_line(char *str)
{
	char	*p;
	char	*line;
	char	*p_line;

	p = str;
	while (*p != '\n' && *p != '\0')
		p++;
	if (*p == '\n')
		p++;
	line = (char *)malloc(sizeof(char) * (p - str) + 1);
	if (!line)
		return (NULL);
	p_line = line;
	while (*str != '\n' && *str != '\0')
		*p_line++ = *str++;
	if (*str == '\n')
		*p_line++ = *str++;
	*p_line = '\0';
	return (line);
}

/*
** This function iterates the string until it finds a breakline
** to ignore the first line. After that, it allocates memory for
** the remaining string and copies the string until the end.
*/

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
		free(save_position);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(p) + 1));
	p = remaining;
	while (*str != '\n' && *str != '\0')
		str++;
	if (*str == '\n')
		str++;
	while (*str != '\0')
		*p++ = *str++;
	*p = '\0';
	free(save_position);
	return (remaining);
}



