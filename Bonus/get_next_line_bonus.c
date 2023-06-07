/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:05:00 by brunrodr          #+#    #+#             */
/*   Updated: 2023/06/07 11:33:02 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function is the same as the get_next_line function from the mandatory part,
** but it can read multiple files. In this case, it reads the files in the order
** they were passed as arguments.
*/

#include "get_next_line_bonus.h"

char		*read_lines(int fd, char *current_line);
static char	find_breakline(char *str);
static char	*get_line(char *str);
static char	*get_remaining(char *str);

/*
** The difference between this function and the get_next_line function from the mandatory part
** is that this function uses a static array of strings to store the file descriptors passed as arguments.
** The value of 4096 is the maximum number of file descriptors allowed by the OS. 
*/

char	*get_next_line(int fd)
{
	static char	*line[4096];
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);
	line[fd] = read_lines(fd, line[fd]);
	if (!ft_strlen(line[fd]))
		return (NULL);
	current_line = get_line(line[fd]);
	if (!current_line)
		return (NULL);
	line[fd] = get_remaining(line[fd]);
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


