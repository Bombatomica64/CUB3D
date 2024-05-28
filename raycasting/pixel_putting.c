/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_putting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 10:16:49 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

// int	reverse_color(int color)
// {
// 	return (color ^ 0x00FFFFFF);
// }

int	reverse_bit(int c)
{
	unsigned int	mask;

	mask = 0;
	mask |= (c & 0xFF) << 24;
	mask |= (c & 0xFF00) << 8;
	mask |= (c & 0xFF0000) >> 8;
	mask |= (c & 0xFF000000) >> 24;
	return (mask);
}

void	better_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_pixel_put(game->mlx, game->win, x, y, color);
}
