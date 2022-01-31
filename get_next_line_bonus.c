/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:09:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/31 01:43:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl[MAX_FD];

	if (!init_gnl(&gnl[fd], fd))
		return (NULL);
	while (read_fd(&gnl[fd]) > 0)
		proceed_data(&gnl[fd]);
	return (quit_gnl(&gnl[fd]));
}
