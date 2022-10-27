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

int	ft_srcfd(t_lastread *lstrd, int fd)
{
	t_lastread	*current;

	current = lstrd;
	while (current)
	{
		if (current->fd == fd)
			return (current->lastbr);
		current = current->next;
	}
	return (-1);
}

void	ft_updatelst(t_lastread *lstrd, int fd, int rd)
{
	t_lastread	*current;

	current = lstrd;
	while (current)
	{
		if (current->fd == fd)
		{
			current->lastbr += rd;
			return ;
		}
		lstrd = current;
		current = current->next;
	}
	if (!lstrd)
		lstrd = malloc(sizeof (t_lastread));
	else
	{
		lstrd->next = malloc(sizeof (t_lastread));
		lstrd = lstrd->next;
	}
	lstrd->fd = fd;
	lstrd->lastbr = rd;
}

char	*get_next_line(int fd)
{
	int		i;
	int		x;
	int		lstbr;
	char	*buffer;
	static t_lastread	*lstrd;

	lstbr = ft_srcfd(lstrd, fd);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (lstbr-- > 0)
		read(fd, buffer, 1);
	x = read(fd, buffer, BUFFER_SIZE);
	if (x < 0)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		buffer[i + 1] = 0;
	ft_updatelst(lstrd, fd, i);
	return (buffer);
}
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
int	main(void)
{
	int	fd;

	fd = open("./sos.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
}
