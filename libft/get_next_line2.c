/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:24:03 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 10:41:38 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	get_next_line2(int fd, char **line)
{
	if (fd < 0)
		return (-1);
	if (*line)
		free (*line);
	*line = NULL;
	*line = get_next_line(fd);
	return (ft_strlen(*line));
}
