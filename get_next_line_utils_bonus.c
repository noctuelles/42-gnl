/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 23:00:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/31 02:06:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*init_gnl(t_gnl *gnl, int fd)
{
	if (!gnl->flags & INIT)
	{
		if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
			return (NULL);
		gnl->buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!gnl->buffer)
			return (NULL);
		gnl->fd = fd;
		gnl->buffer_addr = gnl->buffer;
		gnl->flags |= INIT;
		gnl->flags |= CAN_READ;
	}
	gnl->line = (char *) malloc(sizeof(char));
	if (!gnl->line)
		return (NULL);
	gnl->line[0] = '\0';
	return (gnl->line);
}

char	*quit_gnl(t_gnl *gnl)
{
	if (gnl->readed <= 0)
	{
		free(gnl->buffer_addr);
		gnl->flags &= ~(INIT);
		gnl->flags &= ~(CAN_READ);
		if (gnl->line[0] != '\0')
			return (gnl->line);
		free(gnl->line);
		return (NULL);
	}
	gnl->flags &= ~(LINE_DONE);
	return (gnl->line);
}

void	proceed_data(t_gnl *gnl)
{
	gnl->new_line = ft_strchr(gnl->buffer, '\n');
	if (gnl->new_line)
	{
		gnl->tmp_char = gnl->new_line[1];
		gnl->new_line[1] = '\0';
		gnl->line = ft_strjoin(gnl->line, gnl->buffer);
		gnl->new_line[1] = gnl->tmp_char;
		if (gnl->new_line[1] == '\0')
		{
			gnl->buffer = gnl->buffer_addr;
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
		gnl->buffer = gnl->buffer_addr;
		gnl->flags |= CAN_READ;
	}
}
