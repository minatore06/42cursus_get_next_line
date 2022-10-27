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

void	resetbfr(char **buffer, unsigned int size)
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

char	*get_next_line(int fd)
{
	int		i;
	int		x;
	char	*buffer;
	char	*line;
	static char	*safe;

	if (safe)
	{
		line = ft_strdup(safe);
		free(safe);
		i = ft_strchr(line, '\n');
		if (i != -1)
		{
			safe = ft_strdup(&line[i + 1]);
			line[i + 1] = 0;
			return (line);
		}
	}
	else
		line = malloc(1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)       
	{
		free(buffer);
		return (NULL);
	}
	resetbfr(&buffer, BUFFER_SIZE + 1);
	x = 1;
	while (x > 0)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		if (x < 0)
		{
			free(buffer);
			return (NULL);
		}
		i = ft_strchr(buffer, '\n');
		if (i != -1)
		{
			safe = ft_strdup(&buffer[i + 1]);
			buffer[i + 1] = 0;
			line = ft_strjoin(line, buffer);
			break ;
		}
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

