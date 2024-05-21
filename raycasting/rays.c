/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:13:50 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/21 12:41:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	nor_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	is_wall(double x, double y, t_game *game)
{
	int	i;
	int	j;

	i = floor(y / TILE_SIZE);
	j = floor(x / TILE_SIZE);
	if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
		return (1);
	if (game->map[i][j] == '1')
		return (1);
	return (0);
}

t_img	get_texture(t_game *game)
{
	game->ray.angle = nor_angle(game->ray.angle);
	if (game->ray.flag == 0)
	{
		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
			return (game->txts.imgs[3]);
		else
			return (game->txts.imgs[2]);
	}
	else
	{
		if (game->ray.angle > 0 && game->ray.angle < M_PI)
			return (game->txts.imgs[1]);
		else
			return (game->txts.imgs[0]);
	}
}
