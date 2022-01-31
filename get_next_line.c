/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:09:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/31 01:42:39 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl;

	if (!init_gnl(&gnl, fd))
		return (NULL);
	while (read_fd(&gnl) > 0)
		proceed_data(&gnl);
	return (quit_gnl(&gnl));
}
