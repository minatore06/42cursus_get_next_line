/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:31:55 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/25 15:36:47 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <stdio.h>

static void	resetbfr(char **buffer, unsigned int size)
{
	while(size-- > 0)
		(*buffer)[size] = 0;
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

static char	*past_check(char **safe)
{
	int	i;
	char	*line;

	i = 0;
	if (*safe)
	{
		if (**safe)
		{
			line = ft_strdup(*safe);
			i = ft_strchr(line, '\n');
			free(*safe);
			safe = 0;
			if (i != -1)
			{
				*safe = ft_strdup(&line[i + 1]);
				line[i + 1] = 0;
				return (line);
			}
		}
	}
	return (NULL);
}

int	get_line_save_rest(int i, int x, char **buffer, char **safe, char **line)
{
	if (x <= 0)
	{
		free(*buffer);
		if (!*line)
			*line = NULL;
		return (-1);
	}
	*buffer[BUFFER_SIZE] = 0;
	i = ft_strchr(*buffer, '\n');
	if (i == -1)
		i = ft_strchr(*buffer, -1);
	if (i != -1)
	{
		if ((*buffer)[i + 1])
		{
			if (*safe)
				free(*safe);
			*safe = ft_strdup(&(*buffer)[i + 1]);
		}
		(*buffer)[i + 1] = 0;
		*line = ft_strjoin(*line, *buffer);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	int		i;
	int		x;
	char	*buffer;
	char	*line;
	static char	*safe;

	line = past_check(&safe);
	if (line)
		return (line);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)       
	{
		if (line)
			free(line);
		free(buffer);
		return (NULL);
	}
	x = 1;
	while (x > 0)
	{
		resetbfr(&buffer, BUFFER_SIZE + 1);
		x = read(fd, buffer, BUFFER_SIZE);
		i = get_line_save_rest(0, x, &buffer, &safe, &line);
		if (i == 1)
			break;
		if (i == -1)
			return (line);
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

