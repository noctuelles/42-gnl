/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:09:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/31 15:19:46 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static inline ssize_t	read_fd(t_gnl *gnl)
{
	if (gnl->flags & LINE_DONE)
		return (0);
	if (gnl->flags & CAN_READ)
	{
		gnl->readed = read(gnl->fd, gnl->buffer, BUFFER_SIZE);
		if (gnl->readed > 0)
			gnl->buffer[gnl->readed] = '\0';
	}
	return (gnl->readed);
}

static inline char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}

static void fill_line(t_gnl *gnl)
{
	if (gnl->new_line)
	{
		gnl->tmp_char = gnl->new_line[1];
		gnl->new_line[1] = '\0';
		gnl->line = ft_strjoin(gnl->line, gnl->buffer);
		gnl->new_line[1] = gnl->tmp_char;
		if (gnl->new_line[1] == '\0')
		{
			gnl->buffer = gnl->start_buffer_addr;
			gnl->flags |= CAN_READ;
		}
		else
		{
			gnl->buffer = &gnl->new_line[1];
			gnl->flags &= ~(CAN_READ);
		}
		gnl->flags |= LINE_DONE;
	}
	else
	{
		gnl->line = ft_strjoin(gnl->line, gnl->buffer);
		gnl->buffer = gnl->start_buffer_addr;
		gnl->flags |= CAN_READ;
	}
}

void	proceed_data(t_gnl *gnl)
{
	gnl->new_line = ft_strchr(gnl->buffer, '\n');
	fill_line(gnl);
	if (!gnl->line)
	{
		gnl->readed = 0;
		gnl->flags &= ~(CAN_READ);
		gnl->flags |= MALLOC_EXCEPTION;
	}
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;

	if (!init_gnl(&gnl, fd))
		return (NULL);
	while (read_fd(&gnl) > 0)
		proceed_data(&gnl);
	return (quit_gnl(&gnl));
}
