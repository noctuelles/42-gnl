/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:07:41 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/31 02:34:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>

# define MAX_FD 1024

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

char	*init_gnl(t_gnl *gnl, int fd);
char	*quit_gnl(t_gnl *gnl);
char	*ft_strjoin(char *s1, char *s2);

char	*get_next_line(int fd);

#endif
