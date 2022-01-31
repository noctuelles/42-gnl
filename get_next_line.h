/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/31 02:04:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stddef.h>

typedef enum e_flags
{
	INIT = 1U,
	LINE_DONE = 1U << 1,
	CAN_READ = 1U << 2
}				t_flags;

typedef struct s_gnl
{
	char	*buffer;
	char	*buffer_addr;
	char	*line;
	char	*new_line;
	char	tmp_char;
	int		fd;
	ssize_t	readed;
	int		flags;
}				t_gnl;

void	proceed_data(t_gnl *gnl);
char	*quit_gnl(t_gnl *gnl);
char	*init_gnl(t_gnl *gnl, int fd);
char	*ft_strjoin(char *s1, char *s2);

char	*get_next_line(int fd);

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

static inline size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
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

#endif
