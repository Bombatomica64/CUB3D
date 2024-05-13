/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:24:03 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/13 18:05:35 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	get_next_line2(int fd, char **line)
{
	int	j;

	j = 0;
	if (fd < 0 || !line)
		return (-1);
	if (*line)
		free (*line);
	*line = NULL;
	*line = ft_strtrimfree(get_next_line(fd), "\n", &j);
	return (ft_strlen(*line));
}
