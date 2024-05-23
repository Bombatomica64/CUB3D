/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:13:50 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/23 09:50:14 by lmicheli         ###   ########.fr       */
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
	double	i;
	double	j;

	if (x < 0 || y < 0)
		return (0);
	i = floor(x / TILE_SIZE);
	j = floor(y / TILE_SIZE);
	if (j >= game->map_height || i >= game->map_width)
		return (1);
	if (i < game->map_width && j < game->map_width && i >= 0
		&& j >= 0 && game->map[(int)j])
		if (game->map[(int)j][(int)i] == '1')
			return (0);
	return (1);
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

int	unit_circle(double angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return (1);
	}
	return (0);
}
